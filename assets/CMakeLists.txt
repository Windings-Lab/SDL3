add_custom_target(create_assets_symlink ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${WD_SDL_SOURCE_DIR}/assets/" "${CMAKE_OUTPUT_DIRECTORY}/assets/"
    COMMENT "Creating symbolic link ${WD_SDL_SOURCE_DIR}/assets/ => ${CMAKE_OUTPUT_DIRECTORY}/assets/"
)

add_dependencies(WD_SDL create_assets_symlink)
