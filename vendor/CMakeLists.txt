add_subdirectory(SDL)
add_subdirectory(SDL_image)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE
	SDL3::SDL3
	SDL3_image::SDL3_image
)
target_link_libraries(WD_SDL PUBLIC vendor)

target_include_directories(WD_SDL
	PUBLIC
	$<BUILD_INTERFACE:${SDL3_SOURCE_DIR}/include/SDL3>
)
