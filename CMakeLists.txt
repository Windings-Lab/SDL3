cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|IntelLLVM")
    message("Setting clang debug flags")
    #set(CLANG_OPTIONS "-g3 -ggdb3 -ggdb -gcolumn-info -gfull")
    set(CLANG_OPTIONS "-O0 -g -gdwarf-3")
    set(CMAKE_CXX_FLAGS_DEBUG ${CLANG_OPTIONS})
    set(CMAKE_C_FLAGS_DEBUG ${CLANG_OPTIONS})
    unset(CLANG_OPTIONS)
endif()

set(SOURCES
        main.cpp
        src/WD_engine.cpp
)

set(HEADERS
        include/WD_engine.h
        src/utility/WD_constructors.h
)

add_executable(WD_SDL ${SOURCES} ${HEADERS})

target_include_directories(WD_SDL
        PUBLIC
        $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/src>
)

add_subdirectory(vendor)
target_link_libraries(WD_SDL PRIVATE vendor)
