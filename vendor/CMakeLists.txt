add_subdirectory(libpng)
set(PNG_LIBRARY png_static)
add_library(PNG::PNG ALIAS ${PNG_LIBRARY})
set_property(TARGET ${PNG_LIBRARY} PROPERTY DEBUG_POSTFIX "")
target_include_directories(WD_SDL PRIVATE libpng)
set(PNG_PNG_INCLUDE_DIR "${WD_SDL_SOURCE_DIR}/vendor/libpng;${WD_SDL_BINARY_DIR}/vendor/libpng" CACHE STRING "path of libpng, passed to SDL_image" FORCE)

add_subdirectory(SDL)
add_subdirectory(SDL_image)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE
	PNG::PNG
	SDL3::SDL3
	SDL3_image::SDL3_image
)
target_link_libraries(WD_SDL PUBLIC vendor)

target_include_directories(WD_SDL
	PUBLIC
	$<BUILD_INTERFACE:${SDL3_SOURCE_DIR}/include/SDL3>
)
