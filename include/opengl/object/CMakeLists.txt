target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_object.cppm
    object.cppm
)

add_subdirectory(buffer)
add_subdirectory(shader)
