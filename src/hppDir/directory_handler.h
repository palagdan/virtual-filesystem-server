#pragma once
#include "handler.h"
#include "undefined_method_handler.h"
/**
 * @brief A class that handles directory-related HTTP requests.
 *
 * This class is a subclass of the Handler class and provides implementations for handling GET and POST requests related to directories.
 */
class DirectoryHandler : public Handler {
public:
    virtual void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router) override;
    /**
     * @brief Handles the GET request for directories.
     *
     * This function is called when a GET request is made for directories. It processes the request, generates an appropriate response, and updates the response object accordingly.
     *
     * @param request The HTTPRequest object representing the incoming request.
     * @param response The HTTPResponse object representing the response to be sent.
     * @param router The Router object containing the routing information.
     */
    void getHandle(const HTTPRequest& request, HTTPResponse& response, const Router&);

    /**
     * @brief Handles the POST request for directories.
     *
     * This function is called when a POST request is made for directories. It processes the request, generates an appropriate response, and updates the response object accordingly.
     *
     * @param request The HTTPRequest object representing the incoming request.
     * @param response The HTTPResponse object representing the response to be sent.
     * @param router The Router object containing the routing information.
     */
    void postHandle(const HTTPRequest& request, HTTPResponse& response, const Router&);
};
