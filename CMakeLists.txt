cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        main.cpp
        src/WD_engine.cpp
)

set(HEADERS
        include/WD_engine.h
        src/utility/WD_constructors.h
)

set(GLAD_SOURCES
        src/glad/gl.c
)

set(GLAD_HEADERS
        src/glad/gl.h
        src/glad/khrplatform.h
)

add_executable(WD_SDL ${SOURCES} ${GLAD_SOURCES} ${HEADERS} ${GLAD_HEADERS})

target_include_directories(WD_SDL
        PUBLIC
        $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/src>
)

add_subdirectory(vendor)
target_link_libraries(WD_SDL PRIVATE vendor)
