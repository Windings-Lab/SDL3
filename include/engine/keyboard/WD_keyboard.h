#pragma once

namespace WD::Keyboard
{
    static int Handle_Input(const SDL_Keycode keycode)
    {
        if(keycode == SDLK_ESCAPE)
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }

        return SDL_APP_CONTINUE;
    }
}