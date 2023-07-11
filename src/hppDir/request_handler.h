#pragma once
#include "request.h"
#include "response.h"
#include "handler.h"
#include "directory_handler.h"
#include "script_handler.h"
#include "router.h"
#include "undefined_path_handler.h"
#include "static_file_handler.h"
#include "undefined_method_handler.h"
#include "utils.h"
/**
 * @class RequestHandler
 * @brief Handles HTTP requests and produces corresponding responses.
 */
class RequestHandler {
public:
    /**
     * @brief Constructs a RequestHandler object with the given HTTPRequest.
     * @param request The HTTPRequest object to handle.
     */
    explicit RequestHandler(HTTPRequest request);

    /**
     * @brief Handles the HTTP request and produces an HTTPResponse.
     * @param router The Router object to use for routing the request.
     * @return The HTTPResponse generated based on the request.
     */
    HTTPResponse handlerRequest(const Router& router);

private:
    HTTPRequest m_request;                    /**< The HTTPRequest being handled. */
    std::unique_ptr<Handler> m_handler;        /**< The handler for the request. */
};
