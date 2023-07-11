#include "../hppDir/static_file_handler.h"


void StaticFileHandler::getHandle(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    std::string url = request.getPath();
    std::string address_dir = Utils::getDirectory(url);
    std::string static_file = Utils::getStaticFile(url);
    std::string directory = router.getDirectories()[address_dir];

    std::filesystem::path fileSys = std::filesystem::current_path() / directory;
    std::string file_path = fileSys.string() + "/" + static_file;

    std::ifstream file(file_path, std::ios::binary | std::ios::ate);

    if (file.is_open() && !std::filesystem::is_directory(file_path)) {
        std::streampos file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(file_size);
        if (file.read(buffer.data(), file_size)) {
            // Null-terminate the buffer
            buffer.push_back('\0');

            response.setBody(buffer.data());
            response.setStatus(HTTPResponse::StatusCode::OK); // OK status code

            // Set content type based on the file extension
            std::string file_extension = Utils::getFileExtension(static_file);
            std::string content_type = Utils::getContentType(file_extension);
            response.addHeader("Content-Type", content_type);

            // Update content length based on buffer size
            response.addHeader("Content-Length", std::to_string(buffer.size() - 1));
        } else {
            response.setStatus(HTTPResponse::StatusCode::INTERNAL_SERVER_ERROR); // Internal Server Error status code
            response.setBody("Failed to read the file");
        }

        file.close();
    } else {
        std::string err_msg = "File not found";
        response.setStatus(HTTPResponse::StatusCode::NOT_FOUND); // Not Found status code
        response.addHeader("Content-Length", std::to_string(err_msg.size()));
        response.setBody(err_msg);
    }
}


void StaticFileHandler::deleteHandle(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    std::string url = request.getPath();
    std::string address_dir = Utils::getDirectory(url);
    std::string static_file = Utils::getStaticFile(url);
    std::string directory = router.getDirectories()[address_dir];

    std::filesystem::path fileSys = std::filesystem::current_path() / directory;
    std::string file_path = fileSys.string() + "/"  + static_file;

    if (std::filesystem::exists(file_path)) {
        if (std::filesystem::remove(file_path)) {
            response.setStatus(HTTPResponse::StatusCode::OK);  // OK status code
            response.addHeader("Content-Length","0");
        } else {
            response.setStatus(HTTPResponse::StatusCode::INTERNAL_SERVER_ERROR);  // Internal Server Error status code
            response.addHeader("Content-Length","0");
        }
    } else {
        std::string err_msg = "File not found\n";
        response.setStatus(HTTPResponse::StatusCode::NOT_FOUND);  // Not Found status code
        response.setBody(err_msg);
        response.addHeader("Content-Length",std::to_string(err_msg.size()));
    }
}

void StaticFileHandler::handleRequest(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    // Implement directory handling logic here
    if (request.getStrMethod() == "GET") {
        getHandle(request, response, router);
    } else if (request.getStrMethod() == "DELETE") {
        deleteHandle(request, response, router);
    } else {
        std::unique_ptr<Handler> handler = std::make_unique<UndefinedMethodHandler>();
        handler->handleRequest(request, response, router);
    }
}



