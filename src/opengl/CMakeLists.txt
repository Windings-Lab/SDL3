target_sources(WD_SDL
    PRIVATE
    WD_gl_context.cpp
)

add_subdirectory(buffers)
add_subdirectory(glad)
add_subdirectory(shader)
