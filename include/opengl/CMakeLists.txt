target_sources(WD_SDL
    PUBLIC
    WD_gl_context.h
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        opengl.cppm
)

add_subdirectory(buffers)
add_subdirectory(glad)
add_subdirectory(KHR)
add_subdirectory(shader)
