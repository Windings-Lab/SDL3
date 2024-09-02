target_sources(WD_SDL
    PRIVATE
    engine.cpp
    WD_log.cpp
    window.cpp
)

add_subdirectory(keyboard)
add_subdirectory(math)
