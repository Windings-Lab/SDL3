cmake_minimum_required(VERSION 3.28)
project(WD_SDL LANGUAGES C CXX ASM)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(WD_SDL main.cpp)

target_compile_features(WD_SDL PRIVATE cxx_std_23)

if(MSVC)
	set_target_properties(WD_SDL PROPERTIES
		COMPILE_PDB_NAME WD_SDL
		COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin
	)
endif()

set(compiler_is_msvc "$<CXX_COMPILER_ID:MSVC>")
target_compile_options(WD_SDL PRIVATE
	$<${compiler_is_msvc}:
		  /std:c++latest
		  /Zc:preprocessor
		  /utf-8
		  /EHsc
		  /nologo
		  /UNICODE
		  /FAs
		  $<$<CONFIG:Release>:
			/Ox
			/MD
		  >
		  $<$<CONFIG:Debug>:
			/MDd
		  >
	 >

    $<$<CXX_COMPILER_ID:Clang>:
		-fno-omit-frame-pointer
		-mno-omit-leaf-frame-pointer
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
	$<$<CXX_COMPILER_ID:Clang>:
		-std=c++23
		-stdlib=libc++
	>
)

target_include_directories(WD_SDL
    PUBLIC
    $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/include>
    PRIVATE
    $<BUILD_INTERFACE:${WD_SDL_SOURCE_DIR}/src>
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(vendor)

find_package(Boost)
target_link_libraries(WD_SDL PUBLIC ${Boost_LIBRARIES} ${Boost_HEADERS_LIBRARY})

find_package(glm)
target_link_libraries(WD_SDL PUBLIC glm::glm)
target_compile_definitions(WD_SDL PUBLIC
						   GLM_FORCE_CXX20
)

file(COPY assets/ DESTINATION ${CMAKE_OUTPUT_DIRECTORY}/assets)
