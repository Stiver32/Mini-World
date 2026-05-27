cmake_minimum_required(VERSION 3.20)
project(MiniWorld LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/external/SDL3/cmake")
find_package(SDL3 REQUIRED CONFIG)

add_subdirectory(server)
add_subdirectory(client)