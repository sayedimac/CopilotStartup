#include <httplib.h>
#include <iostream>
#include <string>

/**
 * @brief Example client demonstrating how to interact with the C++ web service
 * 
 * This example shows how to make HTTP requests to the various endpoints
 * exposed by the web service.
 */
int main() {
    const std::string host = "localhost";
    const int port = 8080;

    httplib::Client client(host, port);
    client.set_connection_timeout(5, 0); // 5 seconds

    std::cout << "========================================" << std::endl;
    std::cout << "  C++ Web Service Client Example" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Connecting to: http://" << host << ":" << port << std::endl;
    std::cout << std::endl;

    // Test 1: Health check
    std::cout << "[1] Testing /health endpoint..." << std::endl;
    if (auto res = client.Get("/health")) {
        if (res->status == 200) {
            std::cout << "    Status: " << res->status << std::endl;
            std::cout << "    Response: " << res->body << std::endl;
        } else {
            std::cout << "    Error: " << res->status << std::endl;
        }
    } else {
        std::cout << "    Connection failed!" << std::endl;
        return 1;
    }
    std::cout << std::endl;

    // Test 2: Get time
    std::cout << "[2] Testing /api/time endpoint..." << std::endl;
    if (auto res = client.Get("/api/time")) {
        std::cout << "    Status: " << res->status << std::endl;
        std::cout << "    Response: " << res->body << std::endl;
    } else {
        std::cout << "    Connection failed!" << std::endl;
    }
    std::cout << std::endl;

    // Test 3: Echo POST request
    std::cout << "[3] Testing /api/echo endpoint (POST)..." << std::endl;
    std::string json_payload = R"({"message": "Hello from C++ client!", "value": 42})";
    if (auto res = client.Post("/api/echo", json_payload, "application/json")) {
        std::cout << "    Status: " << res->status << std::endl;
        std::cout << "    Response: " << res->body << std::endl;
    } else {
        std::cout << "    Connection failed!" << std::endl;
    }
    std::cout << std::endl;

    // Test 4: Non-existent endpoint (should return 404)
    std::cout << "[4] Testing non-existent endpoint..." << std::endl;
    if (auto res = client.Get("/api/nonexistent")) {
        std::cout << "    Status: " << res->status << std::endl;
        std::cout << "    Response: " << res->body << std::endl;
    } else {
        std::cout << "    Connection failed!" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  All tests completed!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
