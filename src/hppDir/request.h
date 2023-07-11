#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

/**
 * @class HTTPRequest
 * @brief Class representing an HTTP request.
 *
 * The HTTPRequest class represents an HTTP request with its method, path, version, body, and headers.
 * It provides methods to parse a request, retrieve the request components, and access the headers.
 */
class HTTPRequest {
public:
    /**
     * @brief Parse an HTTP request from a vector of characters.
     * @param request The vector of characters containing the HTTP request.
     *
     * Parses the HTTP request and extracts its components including the method, path, version,
     * body, and headers.
     */
    void parseRequest(const std::vector<char>& request);

    /**
     * @brief Get the HTTP request method.
     * @return The HTTP request method as a string.
     */
    std::string getStrMethod() const;

    /**
     * @brief Get the path of the HTTP request.
     * @return The path of the HTTP request as a string.
     */
    std::string getPath() const;

    /**
     * @brief Get the version of the HTTP request.
     * @return The version of the HTTP request as a string.
     */
    std::string getVersion() const;

    /**
     * @brief Get the body of the HTTP request.
     * @return The body of the HTTP request as a string.
     */
    std::string getBody() const;

    /**
     * @brief Get the headers of the HTTP request.
     * @return The headers of the HTTP request as an unordered map.
     */
    std::unordered_map<std::string, std::string> getHeader() const;


    std::string extractFilenameFromHeaders() const;

private:
    std::string m_str_method;                                  ///< The HTTP request method.
    std::string m_path;                                        ///< The path of the HTTP request.
    std::string m_version;                                     ///< The version of the HTTP request.
    std::string m_body;                                        ///< The body of the HTTP request.
    std::unordered_map<std::string, std::string> m_headers;    ///< The headers of the HTTP request.
};


