target_sources(WD_SDL
    PRIVATE
    object.cpp
    factory.cpp
    storage.cpp
)

add_subdirectory(buffer)
add_subdirectory(vertex)
add_subdirectory(shader)
