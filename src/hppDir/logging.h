#pragma once

#include <ctime>
#include "request.h"
#include "response.h"

/**
 * @class Logging
 * @brief Abstract class for logging functionality.
 *
 * The Logging class provides an interface for logging different types of messages and requests.
 * It also includes a method to retrieve the current date and time for logging purposes.
 */
class Logging {
public:
    /**
     * @brief Destructor.
     *
     * Default virtual destructor for the Logging class.
     */
    virtual ~Logging() = default;

    /**
     * @brief Log an HTTP request.
     * @param request The HTTP request to be logged.
     */
    virtual void logRequest(const HTTPRequest& request) = 0;

    /**
     * @brief Log a warning message.
     * @param message The warning message to be logged.
     */
    virtual void logWarning(const std::string& message) = 0;

    /**
     * @brief Log an error message.
     * @param message The error message to be logged.
     */
    virtual void logError(const std::string& message) = 0;

    /**
     * @brief Log an informational message.
     * @param message The informational message to be logged.
     */
    virtual void logInfo(const std::string& message) = 0;

    /**
     * @brief Log a generic message.
     * @param message The message to be logged.
     */
    virtual void logMessage(const std::string& message) = 0;

    /**
     * @brief Log an HTTP response.
     * @param response The HTTP response to be logged.
     */
    virtual void logResponse(const HTTPResponse& response) = 0;

    /**
     * @brief Get the type of logger.
     * @return The type of logger as a string.
     */
    virtual std::string loggerType() const = 0;

    /**
     * @brief Get the current date and time as a formatted string.
     * @return The current date and time as a string in the format "YYYY-MM-DD-HH-MM-SS".
     */
    std::string logCurrentDate() {
        std::time_t t = std::time(nullptr);   // get current time
        std::tm* now = std::localtime(&t);
        std::ostringstream os;
        os << std::to_string(now->tm_year + 1900) << '-'   // year
           << (now->tm_mon + 1) << '-'                      // month
           << now->tm_mday << '-'                           // day
           << now->tm_hour << '-'                           // hour
           << now->tm_min << '-'                            // minute
           << now->tm_sec;                                  // second
        return os.str();
    };
};
