#pragma once
#include "handler.h"



/**
 * @brief Handles undefined path requests.
 *
 * The UndefinedPathHandler class is responsible for handling requests with undefined paths. It inherits from the Handler class and provides an implementation for handling GET requests.
 */
class UndefinedPathHandler : public Handler {
public:
    /**
     * @brief Handles GET requests with undefined paths.
     *
     * This function handles the GET request with an undefined path. It processes the request, prepares the response, and sets the appropriate status code and headers.
     *
     * @param request The HTTPRequest object representing the GET request.
     * @param response The HTTPResponse object to store the response data.
     * @param router The Router object for routing and configuration.
     */
    void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router) override;
};


