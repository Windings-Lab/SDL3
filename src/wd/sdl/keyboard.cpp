module;

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>

module wd.sdl.Keyboard;

namespace wd::sdl
{
    SDL_AppResult Handle_Input(const SDL_Keycode keycode) noexcept
    {
        if(keycode == SDLK_ESCAPE)
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }

        return SDL_APP_CONTINUE;
    }
}
