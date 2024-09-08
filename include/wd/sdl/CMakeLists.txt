target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_sdl.cppm
    keyboard.cppm
    log.cppm
    window.cppm
)

add_subdirectory(opengl)
