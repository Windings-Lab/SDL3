# SDL3 Development

## Template(Only with submodules)
Feel free to use my SDL preset for development tagged `SDL-Template`. 
It's using submodules and all variables are disabled managed by CMakePreset in SDL
, except Video Subsystem and SDL_Image's png and zlib. Default main code using SDL main callback and I've created Engine class that injecting Window and OpenGL context to avoid global variables

There is a profile cmake.xml for CLion that manages this CMakePreset list. 
If you are not using CLion, then when running cmake use `--preset <preset-name>` to disable unnecessary variables or create new one for yourself
