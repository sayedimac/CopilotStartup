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
    
    // listen() is blocking, so in production you might want to run this in a separate thread
    // Set running_ to true only if listen starts successfully
    bool success = server_->listen(host_, port_);
    
    if (!success) {
        std::cerr << "Failed to start server on " << host_ << ":" << port_ << std::endl;
        return false;
    }
    
    running_ = true;
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

Server::Server(Server&& other) noexcept
    : host_(std::move(other.host_))
    , port_(other.port_)
    , server_(std::move(other.server_))
    , running_(other.running_)
{
    // Ensure moved-from object is in a valid state
    other.running_ = false;
}

Server& Server::operator=(Server&& other) noexcept {
    if (this != &other) {
        // Stop this server if running
        if (running_) {
            stop();
        }
        
        host_ = std::move(other.host_);
        port_ = other.port_;
        server_ = std::move(other.server_);
        running_ = other.running_;
        
        // Ensure moved-from object is in a valid state
        other.running_ = false;
    }
    return *this;
}

} // namespace webservice
