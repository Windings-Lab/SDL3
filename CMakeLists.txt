cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX ASM)

# list(APPEND CMAKE_MODULE_PATH "${WD_SDL_SOURCE_DIR}/cmake")

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp

    # ENGINE
    src/engine/WD_engine.cpp
    include/engine/WD_engine.h
    include/engine/WD_log.h
    src/engine/WD_log.cpp
    include/engine/WD_window.h
    src/engine/WD_window.cpp

    # ENGINE::KEYBOARD
    src/engine/keyboard/WD_keyboard.cpp
    include/engine/keyboard/WD_keyboard.h

    # ENGINE::MATH
    src/engine/math/WD_math.cpp
    include/engine/math/WD_math.h
    include/engine/math/WD_point.h

    # UTILITY
    src/utility/WD_constructors.h

    # OPENGL
    include/opengl/WD_gl_shader.h
    src/opengl/WD_gl_shader.cpp
    include/opengl/WD_gl_context.h
    src/opengl/WD_gl_context.cpp

    # OPENGL::BUFFERS
    src/opengl/buffers/WD_gl_buffer.cpp
    include/opengl/buffers/WD_gl_buffer.h

    # OPENGL::GLAD
    src/opengl/glad/gl.c
    include/opengl/glad/gl.h
    include/opengl/KHR/khrplatform.h
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

target_precompile_headers(WD_SDL PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${WD_SDL_SOURCE_DIR}/include/pch.h>"
)

add_subdirectory(vendor)
target_link_libraries(WD_SDL PUBLIC vendor)

add_custom_command(
    TARGET WD_SDL
    POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink "${WD_SDL_SOURCE_DIR}/assets/" "${CMAKE_OUTPUT_DIRECTORY}/assets/"
    DEPENDS "${CMAKE_OUTPUT_DIRECTORY}/assets/"
    COMMENT "symbolic link ${WD_SDL_SOURCE_DIR}/assets/ => ${CMAKE_OUTPUT_DIRECTORY}/assets/"
)

# Configuration for assembler
set(ASM_SOURCES)

if(NOT ASM_SOURCES MATCHES "")

    set(is_msvc_compiler ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} STREQUAL "MSVC")
    set(is_gnu_compiler ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} STREQUAL "GNU")
    if(${is_msvc_compiler})
        enable_language(ASM_MASM)
    elseif(${is_gnu_compiler})
        enable_language(ASM_NASM)
    endif()


    add_library(nasm_objects OBJECT ${ASM_SOURCES})

    if(${is_msvc_compiler})
        set_target_properties(nasm_objects PROPERTIES LANGUAGE ASM_MASM)
        set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_MASM)
    elseif(${is_gnu_compiler})
        set_target_properties(nasm_objects PROPERTIES LANGUAGE ASM_NASM)
        set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_NASM)
    endif()

    add_executable(WD_ASM ${ASM_SOURCES})

    #add_executable(WD_SDL $<TARGET_OBJECTS:nasm_objects>)

    target_link_libraries(WD_ASM PRIVATE kernel32 user32)
    target_link_options(WD_ASM PRIVATE
        -e WinMain
        -subsystem windows
    )

    target_compile_options(WD_ASM PRIVATE
        -fwin64
    )

endif()
