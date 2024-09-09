target_compile_definitions(WD_SDL PUBLIC
    SDL_MAIN_USE_CALLBACKS
)

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)

target_compile_options(SDL3-static PUBLIC
    $<$<CXX_COMPILER_ID:Clang>:
        -Wno-float-conversion
        -Wno-undef
        -Wno-unused-parameter
        -Wno-unneeded-internal-declaration
    >
)

target_link_libraries(WD_SDL PUBLIC SDL3-static)
