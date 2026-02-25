# C++ Web Service

A modern C++ web service that runs locally, built with C++20 and following industry best practices.

## Features

- **Modern C++20**: Leverages latest C++ standards and idioms
- **HTTP Server**: Lightweight HTTP server using cpp-httplib
- **RESTful API**: Simple REST endpoints for health checks, time, and echo
- **Unit Tests**: Comprehensive test coverage with GoogleTest
- **Code Quality**: Configured with clang-format and clang-tidy
- **Cross-Platform**: Builds on Linux, macOS, and Windows
- **RAII**: Safe resource management with smart pointers
- **Documentation**: Well-documented code with Doxygen-style comments

## Prerequisites

- **CMake** 3.20 or higher
- **C++20 compatible compiler**:
  - GCC 10+ 
  - Clang 12+
  - MSVC 2019+
- **Git** (for fetching dependencies)

## Project Structure

```
src/cpp-service/
├── CMakeLists.txt          # Main build configuration
├── README.md               # This file
├── .clang-format          # Code formatting rules
├── .clang-tidy            # Static analysis configuration
├── include/               # Public headers
│   ├── server.h          # HTTP server interface
│   └── handlers.h        # Request handlers
├── src/                  # Implementation files
│   ├── main.cpp          # Application entry point
│   ├── server.cpp        # Server implementation
│   └── handlers.cpp      # Handler implementations
├── tests/                # Unit tests
│   ├── CMakeLists.txt
│   ├── test_server.cpp
│   └── test_handlers.cpp
└── examples/             # Example applications
    ├── CMakeLists.txt
    └── client_example.cpp
```

## Building

### Quick Start

```bash
# From the cpp-service directory
mkdir build && cd build
cmake ..
cmake --build .
```

### Build Options

```bash
# Enable sanitizers (recommended for development)
cmake .. -DENABLE_SANITIZERS=ON

# Disable tests
cmake .. -DBUILD_TESTS=OFF

# Disable examples
cmake .. -DBUILD_EXAMPLES=OFF

# Release build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

## Running

### Start the Server

```bash
# Default: localhost:8080
./webservice

# Custom port
./webservice 9000

# Custom host and port
./webservice 9000 0.0.0.0
```

### Test the Server

Open your browser and navigate to:
- http://localhost:8080/ - Welcome page with API documentation
- http://localhost:8080/health - Health check endpoint

Or use curl:
```bash
# Health check
curl http://localhost:8080/health

# Get server time
curl http://localhost:8080/api/time

# Echo endpoint (POST)
curl -X POST http://localhost:8080/api/echo \
  -H "Content-Type: application/json" \
  -d '{"message": "Hello, World!"}'
```

### Run Example Client

```bash
# Make sure the server is running first
./example_client
```

## Testing

```bash
# Run all tests
ctest

# Run tests with verbose output
ctest --output-on-failure

# Run specific test
./webservice_tests --gtest_filter=ServerTest.*
```

## API Endpoints

### `GET /`
Returns an HTML page with service information and available endpoints.

**Response:** HTML page

### `GET /health`
Health check endpoint.

**Response:**
```json
{
  "status": "healthy",
  "service": "cpp-webservice"
}
```

### `GET /api/time`
Returns the current server time in ISO 8601 format (UTC).

**Response:**
```json
{
  "time": "2024-12-03T10:59:38Z",
  "timezone": "UTC"
}
```

### `POST /api/echo`
Echoes back the received JSON payload.

**Request:**
```json
{
  "message": "Hello, World!",
  "value": 42
}
```

**Response:**
```json
{
  "received": {
    "message": "Hello, World!",
    "value": 42
  },
  "timestamp": "1701601178000000000"
}
```

## Code Quality

### Formatting

```bash
# Format all source files
find src include tests examples -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### Static Analysis

```bash
# Run clang-tidy
clang-tidy src/*.cpp -- -Iinclude -std=c++20
```

## Development

### Adding New Endpoints

1. Add handler declaration in `include/handlers.h`
2. Implement handler in `src/handlers.cpp`
3. Register route in `src/server.cpp` (`setupRoutes()`)
4. Add tests in `tests/test_handlers.cpp`

### Best Practices

- Use `const` and `noexcept` where appropriate
- Prefer RAII and smart pointers over raw resources
- Follow the single responsibility principle
- Write self-documenting code with clear intent
- Add unit tests for new functionality
- Use structured bindings and modern C++ features
- Keep functions small and focused

## Dependencies

Dependencies are automatically fetched by CMake:

- **cpp-httplib** (v0.14.3): Header-only HTTP library
- **GoogleTest** (v1.14.0): Testing framework (if BUILD_TESTS=ON)

## Troubleshooting

### Port Already in Use

If you see "Failed to start server", another process might be using port 8080:
```bash
# Find process using port 8080
lsof -i :8080  # Linux/macOS
netstat -ano | findstr :8080  # Windows

# Use a different port
./webservice 8081
```

### Build Fails

Ensure you have a C++20 compatible compiler:
```bash
g++ --version  # GCC 10+
clang++ --version  # Clang 12+
```

## License

This project is part of the CopilotStartup repository.

## Contributing

When contributing:
1. Follow the existing code style (use clang-format)
2. Run clang-tidy and fix warnings
3. Add tests for new functionality
4. Update documentation as needed
5. Ensure all tests pass before submitting

## Future Enhancements

- [ ] Add HTTPS support with TLS
- [ ] Implement request logging to file
- [ ] Add configuration file support (JSON/YAML)
- [ ] Database integration examples
- [ ] WebSocket support
- [ ] Rate limiting middleware
- [ ] Authentication/Authorization
- [ ] Metrics and monitoring endpoints
