#include <sstream>
#include "../hppDir/response.h"

void HTTPResponse::setStatus(HTTPResponse::StatusCode status_code) {
    m_status_code = status_code;
}

void HTTPResponse::setBody(const std::string &body) {
    m_body = body;
}

bool HTTPResponse::addHeader(const std::string &key, const std::string &value) {
    if(m_headers.find(key) != m_headers.end())
        return false;
    m_headers[key] = value;
    return true;
}


std::string HTTPResponse::serialize()  {
    std::ostringstream os;
    os << "HTTP/1.1" << " " << getStatusCodeString() << std::endl;
    os << "Content-Type:" << m_headers["Content-Type"] << "; charset=UTF-8"<< std::endl;
    os << "Content-Length:" << m_headers["Content-Length"] << std::endl;
    os << std::endl;
    os << m_body;
    return os.str();
}

std::string HTTPResponse::getStatusCodeString() const {
    switch (m_status_code) {
        case StatusCode::OK:
            return "200 OK";
        case StatusCode::CREATED:
            return "201 Created";
        case StatusCode::NO_CONTENT:
            return "204 No Content";
        case StatusCode::BAD_REQUEST:
            return "400 Bad Request";
        case StatusCode::FORBIDDEN:
            return "403 Forbidden";
        case StatusCode::NOT_FOUND:
            return "404 Not Found";
        case StatusCode::METHOD_NOT_ALLOWED:
            return "405 Method Not Allowed";
        case StatusCode::INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
        default:
            return "Unknown";
    }
}


std::string HTTPResponse::getBody() const {
    return m_body;
}

std::unordered_map<std::string, std::string> HTTPResponse::getHeaders() const {
    return m_headers;
}
