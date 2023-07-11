#include <iostream>
#include "hppDir/server.h"
#include <csignal>

std::unique_ptr<HTTPServer> serverPtr;
void signalHandler(int signal) {
    std::cout << "Signal " << signal << " received. Stopping the server." << std::endl;
    serverPtr.reset();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./[program] [config filename]" << std::endl;
        return 1;
    }

    serverPtr = std::make_unique<HTTPServer>(argv[1]);
    std::signal(SIGINT, signalHandler);   // Register signal handler for SIGINT (Ctrl+C)
    std::signal(SIGTSTP, signalHandler);  // Register signal handler for SIGTSTP (Ctrl+Z)

    try {
        serverPtr->init();
    } catch (const std::runtime_error& e) {
        std::cout << "Server error: " << e.what() << std::endl;
        return 1;
    }

    serverPtr->run();

    return 0;
}
