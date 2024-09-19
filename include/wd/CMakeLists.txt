target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_wd.cppm
    engine.cppm
)

add_subdirectory(sdl)
add_subdirectory(utility)
