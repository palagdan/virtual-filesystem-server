#pragma once
#include "handler.h"
#include "undefined_method_handler.h"
/**
 * @brief Handles static file requests.
 *
 * The StaticFileHandler class is responsible for handling static file requests. It inherits from the Handler class and provides implementations for handling GET and DELETE requests.
 */
class StaticFileHandler : public Handler {
public:

    virtual void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router);
    /**
     * @brief Handles GET requests for static files.
     *
     * This function handles the GET request for static files. It processes the request, prepares the response, and sets the appropriate status code, headers, and file content.
     *
     * @param request The HTTPRequest object representing the GET request.
     * @param response The HTTPResponse object to store the response data.
     * @param router The Router object for routing and configuration.
     */
    virtual void getHandle(const HTTPRequest& request, HTTPResponse& response, const Router& router);

    /**
     * @brief Handles DELETE requests for static files.
     *
     * This function handles the DELETE request for static files. It processes the request, prepares the response, and sets the appropriate status code and headers.
     *
     * @param request The HTTPRequest object representing the DELETE request.
     * @param response The HTTPResponse object to store the response data.
     * @param router The Router object for routing and configuration.
     */
    void deleteHandle(const HTTPRequest& request, HTTPResponse& response, const Router& router);
};

