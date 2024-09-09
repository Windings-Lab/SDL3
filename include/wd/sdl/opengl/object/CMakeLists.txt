target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_object.cppm
    n_creator.cppm
    factory.cppm
    storage.cppm
    object.cppm
)

add_subdirectory(buffer)
add_subdirectory(shader)
add_subdirectory(vertex)
