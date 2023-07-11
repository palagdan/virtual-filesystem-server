#include "../hppDir/utils.h"

std::string Utils::getContentType(const std::string &file_extension){
        // Map file extensions to content types
        std::unordered_map<std::string, std::string> extension_to_content_type = {
                { "txt", "text/plain" },
                { "html", "text/html" },
                { "css", "text/css" },
                { "js", "application/javascript" },
                // Add more mappings as needed
        };

        // Lookup the content type based on the file extension
        auto it = extension_to_content_type.find(file_extension);
        if (it != extension_to_content_type.end()) {
            return it->second;
        }

        // Return a default content type if the extension is not recognized
        return "text/plain";
}

std::string Utils::getDirectory(const std::string address) {
        // Find the position of the last slash in the address
        size_t lastSlashPos = address.rfind('/');
        // Extract the directory path by excluding the static file name
        std::string directory = address.substr(0, lastSlashPos + 1);
        return directory;
}


std::string Utils::getStaticFile(const std::string address){
        // Find the last occurrence of the path separator '/'
        size_t lastSeparator = address.find_last_of('/');
        // Extract the file name by taking the substring after the last separator
        std::string fileName = address.substr(lastSeparator + 1);

        return fileName;
}

std::string Utils::getFileExtension(const std::string &filename){
        size_t dot_pos = filename.rfind('.');
        if (dot_pos != std::string::npos) {
            return filename.substr(dot_pos + 1);
        }
        return "";
}