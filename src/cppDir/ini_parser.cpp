#include "../hppDir/ini_parser.h"

IniParser::IniParser(const std::string & filename) : m_filename(filename){
}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> IniParser::parse() {
    std::ifstream file(m_filename);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open config file: " + m_filename);
    }
    std::string line;
    std::string current_header;
    int line_number = 0;
    while(std::getline(file,line)){
        line_number++;
        if(trim(line).empty() || line[0] == ';')
            continue;
        if(line[0] == '['){
            current_header = line.substr(1, line.find(']') - 1);
            continue;
        }
        std::string::size_type position = line.find('=');
        if(position == std::string::npos)
            throw std::runtime_error("Malformed line in the file!\n" + std::to_string(line_number) + ". " + line);
        const std::string key = trim(toLower(line.substr(0, position)));
        const std::string value = trim( trim(toLower(line.substr(position + 1))));
        m_content[current_header][key] = value;
    }
    if(m_content.empty())
        throw std::runtime_error("No headers found!"  + std::to_string(line_number) + ". ");

    return m_content;
}

void IniParser::clear() {
    m_content.clear();
}

std::string IniParser::toLower(const std::string & src) const {
    std::string lower_string(src);
    transform(lower_string.begin(), lower_string.end(), lower_string.begin(), [](unsigned char c){ return tolower(c);});
    return lower_string;
}

std::string IniParser::trim(const std::string & srcIn) const {
    std::string trim_string(srcIn);
    auto new_end = unique(trim_string.begin(), trim_string.end(), [](char a,char b){ return ::isspace(a) && isspace(b);});
    trim_string.erase(new_end, trim_string.end());

    // Remove leading whitespace
    if (!trim_string.empty() && ::isspace(trim_string.front())) {
        trim_string.erase(trim_string.begin());
    }

    // Remove trailing whitespace
    if (!trim_string.empty() && ::isspace(trim_string.back())) {
        trim_string.erase(trim_string.end() - 1);
    }
    return trim_string;
}