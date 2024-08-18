#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"

namespace WD::Keyboard
{
    int Handle_Input(SDL_Keycode keycode)
    {
        if(keycode == SDLK_ESCAPE)
        {
            SDL_Log("Quiting!");
            return 1;
        }

        return 0;
    }
}
