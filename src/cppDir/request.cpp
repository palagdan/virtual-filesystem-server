#include "../hppDir/request.h"

void HTTPRequest::parseRequest(const std::vector<char>& req) {
    std::string reqStr(req.begin(), req.end());
    std::istringstream ss(reqStr);
    ss >> m_str_method >> m_path >> m_version;
    std::string line;
    std::unordered_map<std::string, std::string> headers;
    while (std::getline(ss, line)) {
        if (line.empty()) {
            // Empty line indicates the end of headers
            break;
        }
        size_t pos = line.find(':');
        std::string name = line.substr(0, pos);
        std::string value = line.substr(pos + 2);
        headers[name] = value;
    }
    m_headers = headers;
    // Read the body
    size_t emptyLinePos = reqStr.find("\r\n\r\n");
    // Extract the body content
    m_body = reqStr.substr(emptyLinePos + 4);
}



std::string HTTPRequest::getStrMethod() const {
    return m_str_method;
}

std::string HTTPRequest::getPath() const {
    return m_path;
}

std::string HTTPRequest::getVersion() const {
    return m_version;
}

std::unordered_map<std::string, std::string> HTTPRequest::getHeader() const {
    return m_headers;
}

std::string HTTPRequest::getBody() const {
    return m_body;
}

std::string HTTPRequest::extractFilenameFromHeaders() const {
    std::string filename;
    // Check if the 'Content-Disposition' header exists
    auto it = m_headers.find("Content-Disposition");
    if (it != m_headers.end()) {
        std::string disposition = it->second;
        // Find the 'filename=' substring within the 'Content-Disposition' header
        size_t filenameStart = disposition.find("filename=");
        if (filenameStart != std::string::npos) {
            // Extract the filename after the 'filename=' substring
            filename = disposition.substr(filenameStart + 9);
            // Remove any surrounding double quotes, if present
            if (!filename.empty()) {
                // Check if the filename starts and ends with a quote character
                    // Remove the surrounding quotes
                    filename = filename.substr(1, filename.size() - 3);
            }
        }
    }

    return filename;
}
