#include <SDL3/SDL_main.h>

import wd.Engine;

SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppInit(void **appstate, int argc, char **argv)
{
    constexpr auto Width = 800;
    constexpr auto Height = 600;

    wd::Engine* Engine = new wd::Engine(Width, Height);
    *appstate = static_cast<void*>(Engine);

    return Engine->OnInit();
}

SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    return Engine->OnEvent(event);
}

SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppIterate(void *appstate)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    return Engine->OnIterate();
}

SDLMAIN_DECLSPEC void SDLCALL SDL_AppQuit(void *appstate)
{
    delete static_cast<wd::Engine*>(appstate);
}
