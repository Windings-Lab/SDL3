target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_wd.cppm
)

add_subdirectory(math)
add_subdirectory(engine)
add_subdirectory(opengl)
add_subdirectory(utility)
