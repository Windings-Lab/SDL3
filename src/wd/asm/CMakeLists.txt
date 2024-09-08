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
