#pragma once
#include "logging.h"
#include <string>
#include <iostream>

/**
 * @class ConsoleLogging
 * @brief Concrete class for logging messages to the console.
 *
 * The ConsoleLogging class is a derived class of Logging that provides functionality to log messages,
 * requests, and responses to the console. It inherits the abstract functions from the Logging class
 * and implements them accordingly.
 */
class ConsoleLogging : public Logging {
public:
    /**
     * @brief Default constructor.
     *
     * Creates a ConsoleLogging object.
     */
    ConsoleLogging() = default;

    /**
     * @brief Log an HTTP request to the console.
     * @param request The HTTP request to be logged.
     */
    void logRequest(const HTTPRequest& request) override;

    /**
     * @brief Log a warning message to the console.
     * @param message The warning message to be logged.
     */
    void logWarning(const std::string& message) override;

    /**
     * @brief Log a generic message to the console.
     * @param message The message to be logged.
     */
    void logMessage(const std::string& message) override;

    /**
     * @brief Log an error message to the console.
     * @param message The error message to be logged.
     */
    void logError(const std::string& message) override;

    /**
     * @brief Log an informational message to the console.
     * @param message The informational message to be logged.
     */
    void logInfo(const std::string& message) override;

    /**
     * @brief Log an HTTP response to the console.
     * @param response The HTTP response to be logged.
     */
    void logResponse(const HTTPResponse& response) override;

    /**
     * @brief Get the type of logger.
     * @return The type of logger as a string.
     */
    std::string loggerType() const override;
};
