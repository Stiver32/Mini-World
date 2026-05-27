add_executable(client main.cpp)

target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/shared
)

target_link_libraries(client PRIVATE SDL3::SDL3)

# copies SDL3.dll next to client.exe on build
if(WIN32)
    add_custom_command(
        TARGET client POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
            $<TARGET_FILE:SDL3::SDL3-shared>
            $<TARGET_FILE_DIR:client>
        VERBATIM
    )
endif()