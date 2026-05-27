add_executable(server "main.cpp" "tcp_server.cpp")

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/shared
)
