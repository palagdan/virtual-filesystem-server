#include "../hppDir/directory_handler.h"



void DirectoryHandler::getHandle(const HTTPRequest& request, HTTPResponse& response, const Router& router) {
    std::string url = request.getPath();
    std::string address_dir = Utils::getDirectory(url);
    std::string directory = router.getDirectories()[address_dir];
    std::filesystem::path fullPath = std::filesystem::current_path() / directory;
    std::ostringstream contentStream;

    // Iterate over the files and directories in the directory
    for (const auto& entry : std::filesystem::directory_iterator(fullPath)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            contentStream << "[File] " << entry.path().filename().string() << '\n';
        } else if (std::filesystem::is_directory(entry.path())) {
            contentStream << "[Directory] " << entry.path().filename().string() << '\n';
        }
    }
    std::string content = contentStream.str();
    // Set the response status and content
    response.setStatus(HTTPResponse::StatusCode::OK);
    response.setBody(content);
    response.addHeader("Content-Length", std::to_string(content.size()));
    response.addHeader("Content-Type", "text/plain; charset=UTF-8");
}

void DirectoryHandler::postHandle(const HTTPRequest& request, HTTPResponse& response, const Router& router) {
    std::string url = request.getPath();
    std::string address_dir = Utils::getDirectory(url);
    std::string directory = router.getDirectories()[address_dir];
    std::string filename = request.extractFilenameFromHeaders();
    // Construct the full file path
    std::filesystem::path fileSys = std::filesystem::current_path() / directory;
    std::string filePath = fileSys.string() + "/" + filename;
    // Open the file for writing
    std::ofstream outputFile(filePath, std::ios::binary);
    if (!outputFile) {
        std::string err_msg = "Failed to create file.";
        response.setStatus(HTTPResponse::StatusCode::INTERNAL_SERVER_ERROR);
        response.addHeader("Content-Length", std::to_string(err_msg.size()));
        response.setBody(err_msg);
        return;
    }

    // Write the request body content to the file
    const std::string requestBody = request.getBody();
    outputFile.write(requestBody.c_str(), requestBody.size());
    outputFile.close();
    response.setBody(requestBody);
    response.addHeader("Content-Length", std::to_string(requestBody.size()));
    std::string file_extension = Utils::getFileExtension(filename);
    std::string content_type = Utils::getContentType(file_extension);
    response.addHeader("Content-Type", content_type);
    response.setStatus(HTTPResponse::StatusCode::CREATED);
}

void DirectoryHandler::handleRequest(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    // Implement directory handling logic here
    if (request.getStrMethod() == "GET") {
        if(router.getDirectoriesPrivate()){
            std::string error_msg = "Forbidden 403\n";
            response.setStatus(HTTPResponse::StatusCode::FORBIDDEN); // Set Not Found status code
            response.setBody(error_msg); // Set response body with an appropriate message
            response.addHeader("Content-Type", "text/plain"); // Set appropriate content type if known
            response.addHeader("Content-Length", std::to_string(error_msg.size()));
        }else{
            getHandle(request, response, router);
        }
    } else if (request.getStrMethod() == "POST") {
        postHandle(request, response, router);
    } else {
        // Handle other methods if needed
        std::unique_ptr<Handler> handler = std::make_unique<UndefinedMethodHandler>();
        handler->handleRequest(request, response, router);
    }
}


