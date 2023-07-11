#include "../hppDir/undefined_method_handler.h"


void UndefinedMethodHandler::handleRequest(const HTTPRequest &request, HTTPResponse &response, const Router &router) {
    std::string error_msg = "404 - Method " + request.getStrMethod() + " not allowed\n";
    router.getScripts();
    response.setStatus(HTTPResponse::StatusCode::METHOD_NOT_ALLOWED); // Set Not Found status code
    response.setBody(error_msg); // Set response body with an appropriate message
    response.addHeader("Content-Type", "text/plain"); // Set appropriate content type if known
    response.addHeader("Content-Length", std::to_string(error_msg.size()));
}
