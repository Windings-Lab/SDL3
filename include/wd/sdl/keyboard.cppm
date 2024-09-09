module;

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>

export module wd.sdl.Keyboard;

export namespace wd::sdl
{
    SDL_AppResult Handle_Input(const SDL_Keycode keycode);
}
