target_sources(WD_SDL
    PUBLIC
    WD_log.h
    WD_window.h
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        m_engine.cppm
        engine.cppm
)

add_subdirectory(math)
add_subdirectory(keyboard)
