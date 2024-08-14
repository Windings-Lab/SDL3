cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX)

# list(APPEND CMAKE_MODULE_PATH "${WD_SDL_SOURCE_DIR}/cmake")

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    # DEFAULT sources
    main.cpp
    src/WD_engine.cpp
    include/WD_engine.h
    include/WD_gl_pipeline.h
    
    # KEYBOARD
    include/keyboard/WD_keyboard.h
    
    # UTILITY
    src/utility/WD_constructors.h

    # GLAD
    src/glad/gl.c
    include/glad/gl.h
    include/KHR/khrplatform.h
)

add_executable(WD_SDL ${SOURCES})

target_compile_features(WD_SDL PRIVATE cxx_std_23)

target_compile_options(WD_SDL PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:
        $<$<CONFIG:Debug>:
            -march=native
            -O0
            -g
            -gdwarf-4
            -fstandalone-debug
        >
    >
)

target_link_options(WD_SDL PRIVATE
    -static-libgcc
    -static-libstdc++
)

target_include_directories(WD_SDL
    PUBLIC
    $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/include>
    PRIVATE
    $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/src>
)

add_subdirectory(vendor)
target_link_libraries(WD_SDL PUBLIC vendor)
