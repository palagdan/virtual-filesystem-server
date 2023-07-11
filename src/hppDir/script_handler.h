#pragma once
#include "handler.h"


/**
 * @class ScriptHandler
 * @brief Handles script execution for HTTP requests.
 *
 * This class inherits from the Handler base class and provides functionality
 * to handle HTTP requests by executing scripts.
 */
class ScriptHandler : public Handler {
public:
    /**
     * @brief Handles the HTTP request by executing the corresponding script.
     * @param request The HTTPRequest object to handle.
     * @param response The HTTPResponse object to populate with the script's output.
     * @param router The Router object to use for routing the request.
     */
    virtual void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router) override;

    /**
     * @brief Replaces placeholders in the command template with the actual filepath.
     * @param commandTemplate The template string containing placeholders.
     * @param filepath The actual filepath to replace the placeholders with.
     * @return The resulting command string with placeholders replaced by the filepath.
     */
    std::string replaceFilepath(const std::string& commandTemplate, const std::string& filepath);
};
