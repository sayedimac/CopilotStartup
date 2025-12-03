#include "server.h"
#include <csignal>
#include <iostream>
#include <memory>

// Global server instance for signal handling
std::unique_ptr<webservice::Server> g_server;

/**
 * @brief Signal handler for graceful shutdown
 * 
 * Handles SIGINT (Ctrl+C) and SIGTERM to stop the server gracefully.
 */
void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "\nReceived shutdown signal, stopping server..." << std::endl;
        if (g_server) {
            g_server->stop();
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        // Parse command line arguments
        std::string host = "localhost";
        int port = 8080;

        if (argc > 1) {
            port = std::stoi(argv[1]);
        }
        if (argc > 2) {
            host = argv[2];
        }

        // Create server instance
        g_server = std::make_unique<webservice::Server>(host, port);

        // Register signal handlers
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);

        std::cout << "========================================" << std::endl;
        std::cout << "  C++ Web Service" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Server will start on: http://" << host << ":" << port << std::endl;
        std::cout << "Press Ctrl+C to stop" << std::endl;
        std::cout << "========================================" << std::endl;

        // Start server (blocking call)
        if (!g_server->start()) {
            std::cerr << "Failed to start server" << std::endl;
            return 1;
        }

        std::cout << "Server stopped" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}
