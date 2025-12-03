include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Test executable
add_executable(webservice_tests
    test_server.cpp
    test_handlers.cpp
)

target_link_libraries(webservice_tests 
    PRIVATE 
    webservice_lib
    GTest::gtest_main
    GTest::gmock
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(webservice_tests)
