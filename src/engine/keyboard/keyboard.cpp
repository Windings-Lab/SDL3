module;

#include "SDL_keycode.h"

module wd_keyboard;


namespace WD::Keyboard
{
    SDL_AppResult Handle_Input(const SDL_Keycode keycode)
    {
        if(keycode == SDLK_ESCAPE)
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }

        return SDL_APP_CONTINUE;
    }
}
