#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include "response.h"
#include "request.h"
#include "router.h"
#include "utils.h"

/**
 * @brief Abstract base class for handling HTTP requests.
 *
 * This class defines the interface for handling different types of HTTP requests. It provides virtual functions for handling GET, POST, and DELETE requests. It also includes utility functions for retrieving file extensions and corresponding content types.
 */
class Handler{
public:

    virtual ~Handler() {};

    /**
     * @brief Handles an HTTP request.
     *
     * This pure virtual function is responsible for handling an HTTP request. Subclasses of Handler must implement this function.
     *
     * @param request The HTTPRequest object representing the incoming request.
     * @param response The HTTPResponse object representing the response to be sent.
     * @param router The Router object containing the registered routes.
     */
    virtual void handleRequest(const HTTPRequest& request, HTTPResponse& response, const Router& router) = 0;
};
