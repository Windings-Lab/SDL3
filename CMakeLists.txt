cmake_minimum_required(VERSION 3.28)
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

project(WD_SDL LANGUAGES C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(compiler_is_msvc "$<CXX_COMPILER_ID:MSVC>")
set(compiler_is_gnu "$<CXX_COMPILER_ID:GNU>")
set(compiler_is_clang "$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>")

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL")

file(GLOB_RECURSE
  project_sources
  CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]pp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.[hc]"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.[hc]pp"
)

add_executable(${PROJECT_NAME}
    ${project_sources}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_std_23
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    NOMINMAX
    SDL_MAIN_USE_CALLBACKS

    $<${compiler_is_msvc}:
        $<$<CONFIG:Debug>:
            _NO_DEBUG_HEAP=1
        >
    >

    $<${compiler_is_gnu}:
		$<$<CONFIG:Debug>:
			_GLIBCXX_DEBUG
		>
	>
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<${compiler_is_msvc}:
        /Zc:preprocessor
        /utf-8
        /std:c++latest

        $<$<CONFIG:Release>:
            /O2 # maximize speed
            /Oy # frame pointer omission
            /Gw # optimize global data
            /GL # whole program optimization
            /Ot # favor fast code
        >
    >

    $<${compiler_is_clang}:
        -march=native
        -DNDEBUG
    >

    $<${compiler_is_gnu}:
        #
    >
)

target_link_options(${PROJECT_NAME}
  PRIVATE
    $<${compiler_is_msvc}:
        # /verbose

        $<$<CONFIG:Release>:
            /opt:ref # eliminate unreferenced functions/data
        >

        $<$<CONFIG:Debug>:
            /opt:ref # eliminate unreferenced functions/data
        >
    >

    $<$<NOT:${compiler_is_msvc}>:
		$<${compiler_is_gnu}:
			$<$<CONFIG:Debug>:
				-lstdc++exp
			>
		>

        -static-libgcc
        -static-libstdc++
    >
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
)

include(cmake-utils)
