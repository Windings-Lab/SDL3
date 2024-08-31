target_precompile_headers(WD_SDL PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${WD_SDL_SOURCE_DIR}/include/pch.h>"
)

add_subdirectory(engine)
add_subdirectory(opengl)
