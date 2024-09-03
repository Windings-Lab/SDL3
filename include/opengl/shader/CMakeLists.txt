target_sources(WD_SDL
    PUBLIC
    WD_gl_shader_program.h
    WD_gl_shader_container.h
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_shader.cppm
        shader.cppm
)
