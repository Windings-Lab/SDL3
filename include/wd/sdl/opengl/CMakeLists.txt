target_sources(WD_SDL
    PUBLIC
    gl.h
    khrplatform.h
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_opengl.cppm
        context.cppm
)

add_subdirectory(object)
