add_subdirectory(zlib)
set(ZLIB_ROOT "${WD_SDL_SOURCE_DIR}/vendor/zlib;${WD_SDL_BINARY_DIR}/vendor/zlib")
# ZLIB_INCLUDE_DIR variable is used by vendored libpng
set(ZLIB_INCLUDE_DIR "${WD_SDL_SOURCE_DIR}/vendor/zlib;${WD_SDL_BINARY_DIR}/vendor/zlib" CACHE STRING "path of zlib, passed to libpng" FORCE)
set(ZLIB_LIBRARY zlibstatic)
if(NOT TARGET ZLIB::ZLIB)
	add_library(ZLIB::ZLIB ALIAS ${ZLIB_LIBRARY})
endif()
# ZLIB_LIBRARIES variable is used by vendored libpng
set(ZLIB_LIBRARIES "${ZLIB_LIBRARY}")
# ZLIB_INCLUDE_DIRS variable is used by vendored libpng
set(ZLIB_INCLUDE_DIRS "${ZLIB_INCLUDE_DIR}")
target_include_directories(${ZLIB_LIBRARY} INTERFACE $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIRS}>)

add_subdirectory(libpng)
set(PNG_LIBRARY png_static)
add_library(PNG::PNG ALIAS ${PNG_LIBRARY})
set_property(TARGET ${PNG_LIBRARY} PROPERTY DEBUG_POSTFIX "")
target_include_directories(WD_SDL PRIVATE libpng)
set(PNG_PNG_INCLUDE_DIR "${WD_SDL_SOURCE_DIR}/vendor/libpng;${WD_SDL_BINARY_DIR}/vendor/libpng" CACHE STRING "path of libpng, passed to SDL_image" FORCE)

add_subdirectory(SDL)
add_subdirectory(SDL_image)

target_include_directories(WD_SDL PRIVATE "${SDL3_SOURCE_DIR}/src/video/khronos")

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE
	ZLIB::ZLIB
	PNG::PNG
	SDL3::SDL3 
    SDL3_image::SDL3_image
)