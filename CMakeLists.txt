cmake_minimum_required(VERSION 3.28)
project(WINDINGS_SDL3 
        VERSION 0.1.0 
        LANGUAGES C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Game main.cpp)

add_subdirectory(vendor)

target_link_libraries(Game PUBLIC vendor)
