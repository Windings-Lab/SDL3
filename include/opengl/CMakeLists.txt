target_sources(WD_SDL
    PUBLIC
    WD_gl_shader.h
    WD_gl_context.h
)

add_subdirectory(buffers)
add_subdirectory(glad)
add_subdirectory(KHR)
