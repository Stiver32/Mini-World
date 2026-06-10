# Devlog

## 2026-05-27
Project setup. Got CMake working with SDL3 prebuilt VC binaries.
Ran into MSVC 14.44 compatibility issues compiling SDL3 from source —
switched to prebuilt binaries to avoid this. Using Winsock2 for
networking instead of SDL3_net for same reason.


## 2026-06-03
Set up a basic TCP server that binds to 127.0.0.1:8080, listens for a connection,
prints whatever the client sends, responsd with a message, then closes the connection.
Used WSAStartup/winsock2 on  Windows. Reference: https://github.com/InancGorgulu/TCP_Tutorial


## 2026-06-08
Built ClientConnection class to mirror TCPServer structure.
CC connects to server and sends input on keydown (currently raw key names)

## 2026-06-09
Set up basic movement and rendering for rectangle.
Next step is to broadcast actual movement/position rather than just key press to server.