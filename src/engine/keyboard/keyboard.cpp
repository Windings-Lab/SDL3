module;

#include <SDL_init.h>
#include <SDL_keycode.h>
#include <SDL_log.h>

module wd.engine.Keyboard;

namespace wd::keyboard
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
