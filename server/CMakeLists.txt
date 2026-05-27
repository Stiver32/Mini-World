add_executable(server "main.cpp")

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/shared
)
