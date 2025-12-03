#pragma once

#include <httplib.h>
#include <string>

namespace webservice::handlers {

/**
 * @brief Health check endpoint handler
 * 
 * Returns a simple JSON response indicating the service is healthy.
 * 
 * @param req HTTP request object
 * @param res HTTP response object
 */
void handleHealth(const httplib::Request& req, httplib::Response& res);

/**
 * @brief Root endpoint handler
 * 
 * Returns a welcome message with service information.
 * 
 * @param req HTTP request object
 * @param res HTTP response object
 */
void handleRoot(const httplib::Request& req, httplib::Response& res);

/**
 * @brief Echo endpoint handler
 * 
 * Echoes back the received message in JSON format.
 * Demonstrates POST request handling.
 * 
 * @param req HTTP request object
 * @param res HTTP response object
 */
void handleEcho(const httplib::Request& req, httplib::Response& res);

/**
 * @brief Get current server time
 * 
 * Returns the current server timestamp in ISO 8601 format.
 * 
 * @param req HTTP request object
 * @param res HTTP response object
 */
void handleTime(const httplib::Request& req, httplib::Response& res);

} // namespace webservice::handlers
