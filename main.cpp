#define SDL_MAIN_USE_CALLBACKS
#include <SDL_main.h>

import wd.Engine;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    constexpr auto Width = 800;
    constexpr auto Height = 600;

    wd::Engine* Engine = new wd::Engine(Width, Height);
    *appstate = static_cast<void*>(Engine);

    return Engine->OnInit();
}

SDL_AppResult SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    return Engine->OnEvent(event);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    return Engine->OnIterate();
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<wd::Engine*>(appstate);
}
