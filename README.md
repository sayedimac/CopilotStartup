# CopilotStartup

A multi-project repository showcasing different technology stacks with best practices.

## Projects

### C++ Web Service (`src/cpp-service/`)

A modern C++20 web service that runs as a local HTTP server.

**Key Features:**
- Modern C++20 with RAII and smart pointers
- RESTful API endpoints (health, time, echo)
- Comprehensive unit tests with GoogleTest
- Cross-platform support (Linux, macOS, Windows)
- Code quality tools (clang-format, clang-tidy)
- CI/CD with GitHub Actions

**Quick Start:**
```bash
cd src/cpp-service
mkdir build && cd build
cmake ..
cmake --build .
./webservice
```

Visit http://localhost:8080 to see the web interface.

**Documentation:** See [src/cpp-service/README.md](src/cpp-service/README.md) for detailed documentation.

### Planned Projects

- **Blazor WASM + .NET 8 Functions** (`src/web/` and `src/api/`)
  - Modern web frontend with Blazor WebAssembly
  - Azure Functions backend (.NET 8 isolated)

## Repository Structure

```
CopilotStartup/
├── .github/
│   ├── workflows/           # CI/CD workflows
│   └── instructions/        # Project-specific instructions
├── src/
│   └── cpp-service/        # C++ web service project
└── README.md               # This file
```

## Development Guidelines

### Code Quality

Each project includes:
- Linting and formatting configuration
- Comprehensive unit tests
- CI/CD pipelines
- Security scanning

### Contributing

1. Follow the existing code style in each project
2. Write tests for new functionality
3. Ensure CI passes before submitting PRs
4. Update documentation as needed

## CI/CD

GitHub Actions workflows are configured for:
- Building and testing on multiple platforms
- Code quality checks (linting, formatting)
- Security scanning (CodeQL)
- Sanitizer tests (where applicable)

## License

This project is a demonstration/learning repository.

## Getting Help

- Check project-specific READMEs for detailed documentation
- Review `.github/instructions/` for project-specific guidelines
- Open an issue for questions or problems
