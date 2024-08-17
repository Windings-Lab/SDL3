#include "engine/WD_engine.h"
#include <SDL3/SDL_video.h>
#include "opengl/WD_shader.h"

WD::Engine::Engine(SDL_Window* window, SDL_GLContext context)
    : NonCopyable()
    , NonMovable()
    , mWindow(window)
    , mContext(context)
{
}

WD::Engine::~Engine()
{
    ShaderPrograms.clear();

    // Clear everything before window destroyed
    SDL_DestroyWindow(mWindow);
}

SDL_Window* WD::Engine::GetWindow() const
{
    return mWindow;
}
