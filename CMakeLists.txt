cmake_minimum_required(VERSION 3.20)
project(tiny-world)

set(CMAKE_CXX_STANDARD 17)

# Fetch SDL3 

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.0
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_net

FetchContent_Declare(
    SDL3_net
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_net.git
    GIT_TAG        main
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3_net)

# SQLite3

find_package(SQLite3 REQUIRED)

# Targets
add_subdirectory(server)
add_subdirectory(client)