#pragma once
#include <string>
#include <unordered_map>

/**
 * @class Utils
 * @brief Utility class providing various helper functions.
 */
class Utils{
public:
      /**
     * @brief Retrieves the file extension from a filename.
     *
     * This function takes a filename as input and returns the file extension.
     *
     * @param filename The filename from which to extract the file extension.
     * @return The file extension as a string, or an empty string if the filename does not have an extension.
     */
    static std::string getFileExtension(const std::string &filename);

    /**
    * @brief Retrieves the content type based on the file extension.
    *
    * This static function takes a file extension as input and returns the corresponding content type. If the file extension 
    * is not recognized, a default content type is returned.
    *
    * @param file_extension The file extension for which to retrieve the content type.
    * @return The content type as a string.
    */
    static std::string getContentType(const std::string &file_extension);

    /**
    * @brief Retrieves the directory path for the specified URL path.
    *
    * This static function retrieves the directory path associated with the specified URL path.
    *
    * @param urlPath The URL path for which to retrieve the directory path.
    * @return The directory path as a string.
    */
    static std::string getDirectory(const std::string address);
    

    /**
    * @brief Retrieves the static file path for the specified URL path.
    *
    * This static function retrieves the static file path associated with the specified URL path.
    *
    * @param urlPath The URL path for which to retrieve the static file path.
    * @return The static file path as a string.
    */
    static std::string getStaticFile(const std::string address);
};