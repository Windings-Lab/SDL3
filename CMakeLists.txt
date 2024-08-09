cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${WD_SDL_SOURCE_DIR}/cmake")
include("${WD_SDL_SOURCE_DIR}/cmake/wdtargets.cmake")

add_executable(WD_SDL main.cpp)

wd_include_directories(
        PUBLIC
        "${WD_SDL_BINARY_DIR}/include"
        "${WD_SDL_SOURCE_DIR}/include"
)

target_include_directories(WD_SDL PRIVATE "$<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/src>")

wd_glob_sources(
        "${WD_SDL_SOURCE_DIR}/src/*.cpp"
)

add_subdirectory(vendor)

target_link_libraries(WD_SDL PRIVATE vendor)
