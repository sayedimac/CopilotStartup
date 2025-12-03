---
applyTo: "src/cpp-service"
---

# C++ Web Service Instructions

## Overview
- This is a modern C++20 web service application
- It runs as a local HTTP server using the cpp-httplib library
- Follows RAII principles and modern C++ best practices
- Uses CMake for build configuration
- Includes comprehensive unit tests with GoogleTest

## Architecture
- **Server**: HTTP server wrapper in `src/server.cpp` with interface in `include/server.h`
- **Handlers**: Request handlers in `src/handlers.cpp` with declarations in `include/handlers.h`
- **Main**: Entry point in `src/main.cpp` with signal handling for graceful shutdown
- **Tests**: Unit tests in `tests/` directory using GoogleTest framework
- **Examples**: Example client application demonstrating API usage

## Development Guidelines

### Code Style
- Use C++20 features (concepts, ranges, constexpr, etc.)
- Follow RAII: Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- Mark functions `[[nodiscard]]` where appropriate
- Use `const` and `noexcept` where applicable
- Prefer value semantics and move operations
- Use structured bindings for readability
- Follow the naming conventions in `.clang-tidy`

### Building
```bash
cd src/cpp-service
mkdir build && cd build
cmake ..
cmake --build .
```

### Testing
```bash
cd src/cpp-service/build
ctest --output-on-failure
```

### Code Quality
- Format code with: `clang-format -i <file>`
- Analyze code with: `clang-tidy <file> -- -Iinclude -std=c++20`
- Run sanitizers during development: `cmake .. -DENABLE_SANITIZERS=ON`

## API Endpoints
- `GET /` - Welcome page with HTML documentation
- `GET /health` - Health check endpoint (JSON)
- `GET /api/time` - Current server time in ISO 8601 format (JSON)
- `POST /api/echo` - Echo back the JSON payload (JSON)

## Dependencies
- **cpp-httplib** (v0.14.3): Header-only HTTP library (auto-fetched by CMake)
- **GoogleTest** (v1.14.0): Testing framework (auto-fetched when BUILD_TESTS=ON)

## Best Practices
- Keep handlers focused and testable
- Use dependency injection for testability
- Document public APIs with Doxygen-style comments
- Write unit tests for new functionality
- Validate inputs and handle errors gracefully
- Use exceptions for error handling (HTTP layer catches them)
- Log important events to stdout/stderr
- Keep the server stateless where possible

## Adding New Endpoints
1. Declare handler function in `include/handlers.h`
2. Implement handler in `src/handlers.cpp`
3. Register route in `Server::setupRoutes()` in `src/server.cpp`
4. Add unit tests in `tests/test_handlers.cpp`
5. Update README.md with endpoint documentation

## Security Considerations
- Validate all input data
- Use safe string operations (no raw char* manipulation)
- Enable sanitizers during development
- Run static analysis with clang-tidy
- Keep dependencies up to date
- Consider rate limiting for production use
- Add authentication/authorization as needed
