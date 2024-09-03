target_sources(WD_SDL
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_opengl.cppm
        context.cppm
)

add_subdirectory(buffers)
add_subdirectory(glad)
add_subdirectory(KHR)
add_subdirectory(shader)
