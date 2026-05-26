add_executable(client main.cpp)

target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(client PRIVATE
    SDL3::SDL3
    SDL3_net::SDL3_net
)