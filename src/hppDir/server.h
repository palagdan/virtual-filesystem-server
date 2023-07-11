#pragma once
#include <string>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <memory>
#include <csignal>
#include "request.h"
#include "response.h"
#include "ini_parser.h"
#include "router.h"
#include "logging.h"
#include "console_logging.h"
#include "file_logging.h"
#include "request_handler.h"

constexpr int BUFFER_SIZE = 8192;

/**
 * @brief Represents an HTTP server.
 *
 * The HTTPServer class implements an HTTP server that listens for incoming requests and handles them accordingly. It provides methods for initializing the server, running the server, displaying server start information, and various initialization steps.
 */
class HTTPServer {
public:
    /**
     * @brief Constructor for the HTTPServer class.
     *
     * @param port The port number on which the server listens.
     */
    HTTPServer(const std::string& port);

    /**
     * @brief Destructor for the HTTPServer class.
     */
    ~HTTPServer();

    /**
     * @brief Runs the HTTP server.
     *
     * This function starts the HTTP server and begins listening for incoming requests. It runs indefinitely until the server is stopped or encounters an error.
     */
    void run();

    /**
     * @brief Displays server start information.
     *
     * This function displays information about the server, such as the IP address, port number, and other configuration details.
     */
    void displayStart();

    /**
     * @brief Initializes the server.
     *
     * This function performs necessary initialization steps for the server, such as setting up the socket and configuring settings.
     */
    void init();

    /**
     * @brief Initializes the socket.
     *
     * This function performs the initialization steps for the socket, including creating the socket file descriptor and setting up the address structure.
     */
    void socket_init();

    /**
     * @brief Initializes the server settings.
     *
     * This function initializes the server settings, such as parsing the configuration file and configuring the router.
     */
    void settings_init();

private:
    std::string m_port;                       /**< The port number on which the server listens. */
    int m_sockfd;                             /**< The socket file descriptor. */
    sockaddr_in m_addr;                       /**< The server's address structure. */
    std::string m_ip_address;                 /**< The server's IP address. */
    IniParser m_parser;                       /**< The configuration file parser. */
    Router m_router;                          /**< The router for handling HTTP requests. */
    std::string m_address_shutdown;           /**< The address for shutting down the server. */
    std::unique_ptr<Logging> m_logger;        /**< The logger for server logging. */
};
