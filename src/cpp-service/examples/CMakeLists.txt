# Example client application
add_executable(example_client
    client_example.cpp
)

target_link_libraries(example_client 
    PRIVATE 
    webservice_lib
)
