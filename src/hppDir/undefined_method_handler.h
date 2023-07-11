#pragma once
#include "handler.h"


/**
 * @brief Handles undefined method requests.
 *
 * The UndefinedMethodHandler class is responsible for handling requests with undefined methods.
 * It inherits from the Handler class and provides an implementation for handling GET requests.
 */
class UndefinedMethodHandler : public Handler {
public:
    /**
     * @brief Handles requests with undefined methods.
     *
     * This function handles the  request with an undefined method. It processes the request,
     * prepares the response, and sets the appropriate status code and headers.
     *
     * @param request The HTTPRequest object representing the GET request.
     * @param response The HTTPResponse object to store the response data.
     * @param router The Router object for routing and configuration.
     */
    virtual void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router) ;
};
