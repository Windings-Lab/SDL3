add_subdirectory(SDL)
add_subdirectory(SDL_image)

# Interface used by ROOT directory and linked from source directory
add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE 
        SDL3::SDL3
        SDL3_image::SDL3_image
)