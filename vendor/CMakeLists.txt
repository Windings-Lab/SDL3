add_subdirectory(zlib)
add_subdirectory(libpng)
add_subdirectory(SDL)
add_subdirectory(SDL_image)

target_include_directories(WD_SDL PRIVATE "${SDL3_SOURCE_DIR}/src/video/khronos")

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE
        zlibstatic
        png_static
        SDL3::SDL3 
        SDL3_image::SDL3_image
)