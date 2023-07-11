#include "../hppDir/server.h"



HTTPServer::HTTPServer(const std::string & config_name) : m_parser(config_name){
}

void HTTPServer::socket_init(){
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sockfd < 0){
        throw std::runtime_error("Error opening socket!");
    }
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(stoi(m_port));
    inet_pton(AF_INET, m_ip_address.c_str(), &m_addr.sin_addr);
    if(bind(m_sockfd, (struct sockaddr*)&m_addr, sizeof m_addr) < 0){
        throw std::runtime_error("Error binding socket to a port " + m_port);
    }
    if(listen(m_sockfd, 1) < 0){
        throw std::runtime_error( "Error listening for incoming connection!" );
    }

    // configure directories
    m_router.configureDirectories(m_router.getDirectories(), m_logger);
}

void HTTPServer::settings_init() {
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> content;
    // parse the config ini file
    try{
        content = m_parser.parse();
    }catch(const std::runtime_error & e){
        std::string msg = std::string("Error parsing configuration file: " ) + e.what();
        throw std::runtime_error(msg);
    }

    //=============== initialize port and ip_address from the config file ===================//
    if(content.find("server_config") == content.end()){
        throw std::runtime_error("Configuration for the server \"server_config\" is not in ini file.");

    }
    else if(content["server_config"].find("port") == content["server_config"].end()){
        throw std::runtime_error("There is no settings for port in configuration file");

    }else if(content["server_config"].find("ip_address") == content["server_config"].end()){
        throw std::runtime_error("There is no settings for ip address in configuration file");
    }
    m_port = content["server_config"]["port"];
    if(m_port.empty())
        throw std::runtime_error("Invalid Port settings");
    m_ip_address = content["server_config"]["ip_address"];
    if(m_ip_address.empty())
        throw std::runtime_error("Invalid IP settings");
    //==================== creating router's endpoints ========================//
    if(content.find("directories") == content.end()){
        throw std::runtime_error("Configuration for the server \"directories\" is not in ini file.");
    }
    for(const auto & route : content["directories"]){
        try {
            m_router.addDirectory(route.first, "server_db" + route.second);
        }catch(const std::runtime_error & e){
            std::string msg = std::string("Error creating router endpoints: ") + e.what();
            throw std::runtime_error(msg);
        }
    }
    //==================== logger initializing ========================//
    if(content.find("log") == content.end()){
        throw std::runtime_error("Configuration for logger is invalid!");
    }else if(content["log"].find("output_type") == content["log"].end()){
        throw std::runtime_error("Configuration for logger is invalid! Missing output type.");
    }
    if(content["log"]["output_type"] == "console"){
        m_logger = std::make_unique<ConsoleLogging>();
    }else if(content["log"]["output_type"] == "file"){
        if(content["log"].find("output_file") == content["log"].end()){
            throw std::runtime_error("Configuration for logger is invalid! Missing output file.");
        }
        m_logger = std::make_unique<FileLogging>(content["log"]["output_file"]);
    }else{
        throw std::runtime_error("Type of logger is undefined: " + content["log"]["output_type"]);
    }

    //==================== logger shutdown =======================//
    if(content.find("shutdown") == content.end()){
        throw std::runtime_error("Configuration for shutdown is invalid!");
    }else{
        if(content["shutdown"].find("address") == content["shutdown"].end()) {
            throw std::runtime_error("Configuration for shutdown is invalid!(Address settings is missing!)");
        }
        m_address_shutdown = content["shutdown"]["address"];
    }
    //==================== script configuration =====================//
    if(content.find("scripts") == content.end()){
        throw std::runtime_error("Configuration for the server \"scripts\" is not in ini file.");
    }
    for(const auto & extension : content["scripts"]){
        try {
            m_router.addScript(extension.first, extension.second);
        }catch(const std::runtime_error & e){
            std::string msg = std::string("Error creating scripts: ") + e.what();
            throw std::runtime_error(msg);
        }
    }

    //==================== parameters =======================//
    if(content.find("parameters") != content.end()) {
        if(content["parameters"].find("directories_private") != content["parameters"].end()) {
            if(content["parameters"]["directories_private"] == "true"){
                m_router.setDirectoriesPrivate(true);
            }else{
                m_router.setDirectoriesPrivate(false);
            }
        }
    }
}

void HTTPServer::init(){
    settings_init();
    socket_init();
}

void HTTPServer::run() {
    displayStart();

    while(true){
        sockaddr_in addr_client;
        socklen_t client_addr_len = sizeof(addr_client);
        int client_socket_fd = accept(m_sockfd, (struct sockaddr*)&addr_client, &client_addr_len);
        if(client_socket_fd < 0){
            m_logger->logWarning("Error accepting incoming connection");
            continue;
        }
        m_logger->logInfo("Client socket fd " + std::to_string(client_socket_fd) + " connected to the server.");
        HTTPRequest request;
        HTTPResponse response;
        char buffer[BUFFER_SIZE + 10];
        int valread = 0;
        std::vector<char> requestContainer;

        valread = read(client_socket_fd, buffer, sizeof(buffer));
        if (valread <= 0) {
            close(client_socket_fd);
            continue;
        }

        if (valread > BUFFER_SIZE){
            std::string warning_msg = "Request is too big. Max 8 KiB.";
            m_logger->logWarning(warning_msg);
            response.setStatus(HTTPResponse::StatusCode::BAD_REQUEST);
            response.setBody(warning_msg);
            response.addHeader("Content-Length", std::to_string(warning_msg.size()));
            std::string serializedData = response.serialize();
            size_t dataSize = serializedData.size();
            send(client_socket_fd, serializedData.c_str(), dataSize, 0);
            close(client_socket_fd);
            continue;
        }

        for (auto i = 0; i < valread; i++) {
            requestContainer.push_back(buffer[i]);
        }

        try{
            request.parseRequest(requestContainer);
        }catch (const std::runtime_error & e){
            m_logger->logWarning(e.what());
        }
        m_logger->logRequest(request);

        
        // address for shutdown
        if(request.getPath() == m_address_shutdown && request.getStrMethod() == "POST"){
            m_logger->logInfo("Server is shutting down");
            response.setStatus(HTTPResponse::StatusCode::OK);
            response.addHeader("Content-Length", "0");
            std::string serializedData = response.serialize();
            size_t dataSize = serializedData.size();
            send(client_socket_fd, serializedData.c_str(), dataSize, 0);
            close(client_socket_fd);
            break;
        }
        RequestHandler handler(request);
        response = handler.handlerRequest(m_router);
        std::string serializedData = response.serialize();
        size_t dataSize = serializedData.size();
        m_logger->logResponse(response);
        send(client_socket_fd, serializedData.c_str(), dataSize, 0);
        m_logger->logInfo("Client socket fd " + std::to_string(client_socket_fd) + " connection closed");
        close(client_socket_fd);
    }
}

void HTTPServer::displayStart() {
    m_logger->logMessage( "   _________                                \n"
                 " /   _____/ ______________  __ ___________ \n"
                 " \\_____  \\_/ __ \\_  __ \\  \\/ // __ \\_  __ \\\n"
                 " /        \\  ___/|  | \\/\\   /\\  ___/|  | \\/\n"
                 "/_______  /\\___  >__|    \\_/  \\___  >__|   \n"
                 "        \\/     \\/                 \\/ .\n"
    );
    m_logger->logInfo( "Server listening on port: " + m_port);
    m_logger->logInfo( "IP Address: " +  m_ip_address);
    m_logger->logInfo("Available endpoints for the directories: ");
    for(const auto& dir : m_router.getDirectories()){
        m_logger->logInfo("\"" + dir.first + "\"" + " -> " + "\"" + dir.second + "\"");
    }
    m_logger->logInfo("Available scripts extensions: ");
    for(const auto& script : m_router.getScripts()){
        m_logger->logInfo("\"" + script.first + "\"" + " -> " + "\"" + script.second + "\"");
    }
    m_logger->logInfo( "Logger mode: " + m_logger->loggerType());
}


HTTPServer::~HTTPServer() {
    m_logger->logMessage("Server is stopped!");
    close(m_sockfd);
}
