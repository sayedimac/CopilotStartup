#include "handlers.h"
#include <chrono>
#include <iomanip>
#include <sstream>

namespace webservice::handlers {

void handleHealth(const httplib::Request& /*req*/, httplib::Response& res) {
    res.status = 200;
    res.set_content(R"({"status": "healthy", "service": "cpp-webservice"})", 
                    "application/json");
}

void handleRoot(const httplib::Request& /*req*/, httplib::Response& res) {
    res.status = 200;
    const char* html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>C++ Web Service</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        h1 { color: #0078D4; }
        .endpoint { background: #f5f5f5; padding: 10px; margin: 10px 0; border-left: 3px solid #0078D4; }
        code { background: #e8e8e8; padding: 2px 6px; border-radius: 3px; }
    </style>
</head>
<body>
    <h1>C++ Web Service</h1>
    <p>Welcome to the modern C++ web service running locally!</p>
    
    <h2>Available Endpoints:</h2>
    <div class="endpoint">
        <strong>GET /health</strong><br>
        Health check endpoint - returns service status
    </div>
    <div class="endpoint">
        <strong>GET /api/time</strong><br>
        Returns current server time in ISO 8601 format
    </div>
    <div class="endpoint">
        <strong>POST /api/echo</strong><br>
        Echoes back the JSON payload you send<br>
        Example: <code>{"message": "Hello, World!"}</code>
    </div>
    
    <h3>Try it out:</h3>
    <p>
        <code>curl http://localhost:8080/health</code><br>
        <code>curl http://localhost:8080/api/time</code><br>
        <code>curl -X POST http://localhost:8080/api/echo -H "Content-Type: application/json" -d '{"message":"Hello"}'</code>
    </p>
</body>
</html>
)";
    
    res.set_content(html, "text/html");
}

void handleEcho(const httplib::Request& req, httplib::Response& res) {
    if (req.body.empty()) {
        res.status = 400;
        res.set_content(R"({"error": "Request body is empty"})", "application/json");
        return;
    }

    // Echo back the received body in a JSON wrapper
    std::ostringstream json;
    json << R"({"received": )" << req.body << R"(, "timestamp": ")" 
         << std::chrono::system_clock::now().time_since_epoch().count() 
         << R"("})";
    
    res.status = 200;
    res.set_content(json.str(), "application/json");
}

void handleTime(const httplib::Request& /*req*/, httplib::Response& res) {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&time_t_now), "%Y-%m-%dT%H:%M:%SZ");
    
    std::ostringstream json;
    json << R"({"time": ")" << oss.str() << R"(", "timezone": "UTC"})";
    
    res.status = 200;
    res.set_content(json.str(), "application/json");
}

} // namespace webservice::handlers
