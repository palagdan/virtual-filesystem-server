#include "../hppDir/undefined_path_handler.h"

void UndefinedPathHandler::handleRequest(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    std::string error_msg = "404 - Page " + request.getPath() + " Not Found\n";
    router.getScripts();
    response.setStatus(HTTPResponse::StatusCode::NOT_FOUND); // Set Not Found status code
    response.setBody(error_msg); // Set response body with an appropriate message
    response.addHeader("Content-Type", "text/plain"); // Set appropriate content type if known
    response.addHeader("Content-Length", std::to_string(error_msg.size()));
}

