#include "../hppDir/router.h"

void Router::addDirectory(const std::string& route, const std::string& directory) {
    if(route.empty() || route[0] != '/')
        throw std::runtime_error("Route is empty or has inappropriate format. It must begin with '/' .");

    if(directory.empty())
        throw std::runtime_error("Directory that you provided is invalid.");

    if(m_directories.find(route) != m_directories.end())
        throw std::runtime_error("Directory already exists!");
    m_directories[route] = directory;
}


std::unordered_map<std::string, std::string> Router::getDirectories() const {
    return m_directories;
}

bool Router::deleteDirectory(const std::string & src) {
    if(m_directories.find(src) == m_directories.end()){
        return false;
    }
    m_directories.erase(src);
    return true;
}


void Router::configureDirectories(const std::unordered_map<std::string, std::string>& directories, std::unique_ptr<Logging> & logger) const {
    for (const auto& route : directories) {
        try {
            logger->logInfo(std::filesystem::current_path() / route.second);
            std::filesystem::create_directory(std::filesystem::current_path() / route.second);
        } catch (const std::exception& e) {
            std::string msg = std::string("Error creating directory: ") + e.what();
            logger->logError(msg);
        }
    }
}

void Router::setDirectoriesPrivate(const bool directories_private) {
    m_directories_private = directories_private;
}

bool Router::getDirectoriesPrivate() const {
    return m_directories_private;
}

void Router::addScript(const std::string &extension, const std::string &command) {
    if(m_scripts_extensions.find(extension) != m_scripts_extensions.end())
        throw std::runtime_error("Extension already exists!");
    m_scripts_extensions[extension] = command;
}

std::unordered_map<std::string, std::string>  Router::getScripts() const {
    return m_scripts_extensions;
}
