real-time multiplayer world built in C++ and SDL3.
Players can move around a shared, persistent world; eventual expansion to allow for entering instanced zones.
Built to learn game server architecture

## Dependencies
- SDL3
- SQLite3
- CMake 

## Setup
1. Download SDL3-devel-x.x.x-VC.zip from github.com/libsdl-org/SDL/releases
2. Extract and rename to `SDL3`, place in `external/`
3. cmake -B build && cmake --build build

## Running
./build/server/Debug/server.exe    
./build/client/Debug/client.exe    

## Status
Early development
Hiatus; need to read a bit more on some socket programming for next steps and revisit this
