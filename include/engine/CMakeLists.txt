target_sources(WD_SDL
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_engine.cppm
        engine.cppm
        window.cppm
        log.cppm
)

add_subdirectory(keyboard)
