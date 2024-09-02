module;

#include "SDL_init.h"
#include "SDL_keycode.h"

export module wd_keyboard;

export namespace WD::Keyboard
{
    SDL_AppResult Handle_Input(const SDL_Keycode keycode);
}
