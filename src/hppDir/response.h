#pragma once
#include <string>
#include <unordered_map>

/**
 * @brief Represents an HTTP response.
 *
 * This class encapsulates the information related to an HTTP response, including status code, body, and headers. It provides various methods for manipulating and retrieving the response data.
 */
class HTTPResponse {
public:
    /**
     * @brief Enumerates the possible HTTP status codes.
     */
    enum class StatusCode {
        OK = 200,                   /**< Indicates a successful response. */
        CREATED = 201,              /**< Indicates successful creation of a new resource. */
        NO_CONTENT = 204,           /**< Indicates a successful response with no content. */
        BAD_REQUEST = 400,          /**< Indicates a malformed or invalid request. */
        FORBIDDEN = 403,            /**< Indicates that access to the requested resource is forbidden. */
        NOT_FOUND = 404,            /**< Indicates that the requested resource was not found. */
        INTERNAL_SERVER_ERROR = 500,/**< Indicates an internal server error. */
        METHOD_NOT_ALLOWED = 405    /**< Indicates that the requested method is not allowed for the resource. */
    };

    /**
     * @brief Sets the status code of the HTTP response.
     *
     * @param statusCode The status code to set.
     */
    void setStatus(StatusCode statusCode);

    /**
     * @brief Sets the body of the HTTP response.
     *
     * @param body The body content to set.
     */
    void setBody(const std::string& body);

    /**
     * @brief Adds a header to the HTTP response.
     *
     * @param key The header key.
     * @param value The header value.
     * @return `true` if the header was added successfully, `false` otherwise.
     */
    bool addHeader(const std::string& key, const std::string& value);

    /**
     * @brief Retrieves the string representation of the status code.
     *
     * @return The string representation of the status code.
     */
    std::string getStatusCodeString() const;

    /**
     * @brief Retrieves the content type of the HTTP response.
     *
     * @return The content type as a string.
     */
    std::string getContentType() const;

    /**
     * @brief Retrieves the content length of the HTTP response body.
     *
     * @return The content length as an integer.
     */
    int getContentLength() const;

    /**
     * @brief Retrieves the body of the HTTP response.
     *
     * @return The response body as a string.
     */
    std::string getBody() const;

    /**
     * @brief Retrieves the headers of the HTTP response.
     *
     * @return The headers as an unordered map of key-value pairs.
     */
    std::unordered_map<std::string, std::string> getHeaders() const;

    /**
     * @brief Serializes the HTTP response into a string.
     *
     * @return The serialized string representation of the HTTP response.
     */
    std::string serialize();

private:
    StatusCode m_status_code;                           /**< The status code of the HTTP response. */
    std::string m_body;                                 /**< The body content of the HTTP response. */
    std::unordered_map<std::string, std::string> m_headers; /**< The headers of the HTTP response. */
};

