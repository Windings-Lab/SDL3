set(BUILD_SHARED_LIBS OFF)
add_subdirectory(SDL)
add_subdirectory(SDL_image)
set(BUILD_SHARED_LIBS ON)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE 
        SDL3::SDL3 
        SDL3_image::SDL3_image
)