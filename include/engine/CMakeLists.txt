target_sources(WD_SDL
    PUBLIC
    WD_log.h
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_engine.cppm
        engine.cppm
        window.cppm
)

add_subdirectory(math)
add_subdirectory(keyboard)
