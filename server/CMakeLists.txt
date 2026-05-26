add_executable(server main.cpp)

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/shared   # so you can include protocol.h
)

target_link_libraries(server PRIVATE
    SDL3_net::SDL3_net
    SQLite::SQLite3
)