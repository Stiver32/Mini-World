add_executable(server "main.cpp" "tcp_server.cpp")

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(server PRIVATE Ws2_32)
