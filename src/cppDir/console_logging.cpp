#include "../hppDir/console_logging.h"

void ConsoleLogging::logResponse(const HTTPResponse & req){
    std::cout << "Response: " << logCurrentDate() << " | " << " \"HTTP/1.1\" " << req.getStatusCodeString() << std::endl;
    std::cout << "Content-Type:" << " " << req.getHeaders()["Content-Type"]<< ";charset=UTF-8" << std::endl;
    std::cout << "Content-Length:" << " " << req.getHeaders()["Content-Length"] << std::endl;
    std::cout << std::endl;
    std::cout << req.getBody();
}

void ConsoleLogging::logRequest(const HTTPRequest & req){
    std::cout << "Request: " << logCurrentDate() << " | " << req.getStrMethod() << " " << req.getPath() << " " << req.getVersion() << std::endl;
    std::cout << "Accept:" << req.getHeader()["Accept"] << std::endl;
    std::cout << req.getBody() << std::endl;
}

std::string ConsoleLogging::loggerType() const {
    return "console";
}

void ConsoleLogging::logWarning(const std::string & src) {
    std::cout << logCurrentDate() << " WARN " << src << std::endl;
}

void ConsoleLogging::logInfo(const std::string & src) {
    std::cout << logCurrentDate() << " INFO "   << src << std::endl;
}

void ConsoleLogging::logError(const std::string & src) {
    std::cout << logCurrentDate() << " ERROR " << src << std::endl;
}

void ConsoleLogging::logMessage(const std::string & src) {
    std::cout << logCurrentDate()  << " " << src << std::endl;
}

