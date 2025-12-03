#pragma once

#include <httplib.h>
#include <memory>
#include <string>

namespace webservice {

/**
 * @brief HTTP server wrapper providing a simple interface for running a web service
 * 
 * This class encapsulates the HTTP server implementation and provides
 * methods to configure and run the service locally.
 */
class Server {
public:
    /**
     * @brief Construct a new Server object
     * @param host The host address to bind to (default: "localhost")
     * @param port The port number to listen on (default: 8080)
     */
    explicit Server(std::string host = "localhost", int port = 8080);

    /**
     * @brief Destroy the Server object
     */
    ~Server();

    // Delete copy operations (single instance pattern)
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    // Allow move operations
    Server(Server&&) noexcept = default;
    Server& operator=(Server&&) noexcept = default;

    /**
     * @brief Start the HTTP server
     * @return true if server started successfully, false otherwise
     */
    [[nodiscard]] bool start();

    /**
     * @brief Stop the HTTP server
     */
    void stop();

    /**
     * @brief Check if the server is currently running
     * @return true if running, false otherwise
     */
    [[nodiscard]] bool isRunning() const noexcept;

    /**
     * @brief Get the host address
     * @return const std::string& Host address
     */
    [[nodiscard]] const std::string& getHost() const noexcept { return host_; }

    /**
     * @brief Get the port number
     * @return int Port number
     */
    [[nodiscard]] int getPort() const noexcept { return port_; }

private:
    std::string host_;
    int port_;
    std::unique_ptr<httplib::Server> server_;
    bool running_;

    void setupRoutes();
};

} // namespace webservice
