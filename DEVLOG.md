# Devlog

## 2026-05-27
Project setup. Got CMake working with SDL3 prebuilt VC binaries.
Ran into MSVC 14.44 compatibility issues compiling SDL3 from source —
switched to prebuilt binaries to avoid this. Using Winsock2 for
networking instead of SDL3_net for same reason.