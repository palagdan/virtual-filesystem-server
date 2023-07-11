
#include "../hppDir/file_logging.h"

FileLogging::FileLogging(const std::string &target_file) : m_os(target_file){

}

void FileLogging::logRequest(const HTTPRequest & req)  {
    if(m_os.is_open()){
        m_os << "Request: " << logCurrentDate() << " | " << req.getStrMethod() << " " << req.getPath() << " " << req.getVersion() << std::endl;
        m_os << "Accept:" << req.getHeader()["Accept"] << std::endl;
        m_os << req.getBody() << std::endl;
        m_os << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}

void FileLogging::logResponse(const HTTPResponse & req)  {
    if(m_os.is_open()){
        m_os << "Response: " << logCurrentDate() << " | " << " \"HTTP/1.1\" " << req.getStatusCodeString() << std::endl;
        m_os << "Content-Type:" << " " << req.getHeaders()["Content-Type"]<< ";charset=UTF-8" << std::endl;
        m_os << "Content-Length:" << " " << req.getHeaders()["Content-Length"] << std::endl;
        m_os << std::endl;
        m_os << req.getBody() << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}

std::string FileLogging::loggerType() const {
    return "File";
}

void FileLogging::logWarning(const std::string & src) {

    if(m_os.is_open()){
        m_os << logCurrentDate() << " WARN "  << src << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}
void FileLogging::logInfo(const std::string & src) {
    if(m_os.is_open()){
        m_os << logCurrentDate() << " INFO " << src << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}
void FileLogging::logError(const std::string & src) {
    if(m_os.is_open()){
        m_os << logCurrentDate() << " ERROR " << src << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}

void FileLogging::logMessage(const std::string & src) {
    if(m_os.is_open()){
        m_os << logCurrentDate() << " " << src << std::endl;
    }else{
        throw std::runtime_error("Error: logger file is closed " + m_target_file);
    }
}


