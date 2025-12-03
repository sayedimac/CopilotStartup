cmake_minimum_required(VERSION 3.20)

project(CppWebService 
    VERSION 1.0.0
    DESCRIPTION "Modern C++ Web Service"
    LANGUAGES CXX
)

# Set C++20 as the standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_SANITIZERS "Enable sanitizers (ASan, UBSan)" OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Sanitizers (for development builds)
if(ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Fetch cpp-httplib (header-only HTTP library)
include(FetchContent)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.3
)
FetchContent_MakeAvailable(httplib)

# Main library (static library for reuse in tests and examples)
add_library(webservice_lib STATIC
    src/server.cpp
    src/handlers.cpp
)

target_include_directories(webservice_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(webservice_lib PUBLIC httplib::httplib)

# Main executable
add_executable(webservice
    src/main.cpp
)

target_link_libraries(webservice PRIVATE webservice_lib)

# Add pthread support for Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(webservice PRIVATE pthread)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
install(TARGETS webservice
    RUNTIME DESTINATION bin
)
