#include "server.h"
#include "handlers.h"
#include <iostream>
#include <stdexcept>

namespace webservice {

Server::Server(std::string host, int port)
    : host_(std::move(host))
    , port_(port)
    , server_(std::make_unique<httplib::Server>())
    , running_(false)
{
    if (port_ <= 0 || port_ > 65535) {
        throw std::invalid_argument("Port must be between 1 and 65535");
    }

    setupRoutes();
}

Server::~Server() {
    if (running_) {
        stop();
    }
}

void Server::setupRoutes() {
    // Health check endpoint
    server_->Get("/health", handlers::handleHealth);

    // Root endpoint
    server_->Get("/", handlers::handleRoot);

    // Echo endpoint (POST)
    server_->Post("/api/echo", handlers::handleEcho);

    // Time endpoint
    server_->Get("/api/time", handlers::handleTime);

    // Error handler
    server_->set_error_handler([](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_content(R"({"error": "Not Found", "status": 404})", "application/json");
    });

    // Logger
    server_->set_logger([](const httplib::Request& req, const httplib::Response& res) {
        std::cout << "[" << req.method << "] " << req.path 
                  << " -> " << res.status << std::endl;
    });
}

bool Server::start() {
    if (running_) {
        std::cerr << "Server is already running" << std::endl;
        return false;
    }

    std::cout << "Starting server on " << host_ << ":" << port_ << std::endl;
    
    running_ = true;
    
    // listen() is blocking, so in production you might want to run this in a separate thread
    if (!server_->listen(host_, port_)) {
        running_ = false;
        std::cerr << "Failed to start server on " << host_ << ":" << port_ << std::endl;
        return false;
    }

    return true;
}

void Server::stop() {
    if (!running_) {
        return;
    }

    std::cout << "Stopping server..." << std::endl;
    server_->stop();
    running_ = false;
}

bool Server::isRunning() const noexcept {
    return running_;
}

} // namespace webservice
