#include "WD_engine.h"

#include <SDL3/SDL_video.h>

WD::Engine::Engine(SDL_Window* window, SDL_GLContext context)
    : NonCopyable()
    , NonMovable()
    , mWindow(window)
    , mContext(context)
{
}

WD::Engine::~Engine()
{
    SDL_DestroyWindow(mWindow);
}

SDL_Window& WD::Engine::GetWindow() const
{
    return *mWindow;
}
