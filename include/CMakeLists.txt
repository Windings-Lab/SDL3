target_precompile_headers(WD_SDL PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${WD_SDL_SOURCE_DIR}/include/pch.h>"
)

target_sources(WD_SDL
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    m_wd.cppm
)

add_subdirectory(math)
add_subdirectory(engine)
add_subdirectory(opengl)
