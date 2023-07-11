#pragma once
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>

/**
 * @class IniParser
 * @brief Class for parsing and manipulating INI files.
 *
 * The IniParser class provides functionality to parse and manipulate INI (Initialization) files.
 * It allows reading and retrieving the content of INI files as a nested unordered map structure.
 * Additionally, it includes utility functions for string manipulation, such as converting to lowercase
 * and trimming whitespace.
 */
class IniParser {
public:
    /**
     * @brief Constructor.
     * @param filename The name of the INI file to be parsed.
     *
     * Creates an IniParser object with the specified INI file name.
     */
    IniParser(const std::string& filename);

    /**
     * @brief Parse the INI file and return the content as a nested unordered map.
     * @return The parsed content of the INI file as an unordered map.
     *
     * Parses the INI file specified in the constructor and returns its content as a nested unordered map.
     * The outer unordered map represents the sections of the INI file, where each section is a key-value pair.
     * The inner unordered map represents the key-value pairs within each section.
     */
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parse();

    /**
     * @brief Clear the parsed content.
     *
     * Clears the parsed content stored in the IniParser object.
     */
    void clear();

    /**
     * @brief Convert a string to lowercase.
     * @param str The string to be converted.
     * @return The lowercase version of the input string.
     *
     * Converts the input string to lowercase and returns the result.
     */
    std::string toLower(const std::string& str) const;

    /**
     * @brief Trim leading and trailing whitespace from a string.
     * @param str The string to be trimmed.
     * @return The trimmed version of the input string.
     *
     * Removes leading and trailing whitespace characters from the input string and returns the result.
     */
    std::string trim(const std::string& str) const;
    
private:
    std::string m_filename; /**< The name of the INI file. */
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_content; /**< The parsed content of the INI file. */

};
