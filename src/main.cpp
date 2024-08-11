#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "WD_engine.h"

int SDL_AppInit(void** appstate, int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_SetError("SDL failed to initialize!");
        SDL_LogError(0, SDL_GetError());

        return SDL_APP_FAILURE;
    }

    // Version 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // All core and deprecated OPENGL function are available
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    constexpr int Width = 800;
    constexpr int Height = 600;

    auto* Window = SDL_CreateWindow("Hello SDL and OpenGL", Width, Height, SDL_WINDOW_OPENGL);
    if (!Window)
    {
        SDL_SetError("SDL failed to initialize!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    auto* Context = SDL_GL_CreateContext(Window);
    if (!Context)
    {
        SDL_DestroyWindow(Window);
        SDL_SetError("OpenGL Context failed to create!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    auto* Engine = new WD::Engine(Window, Context);
    *appstate = static_cast<void*>(Engine);

    return SDL_APP_CONTINUE;
}

int SDL_AppEvent(void* appstate, const SDL_Event* event)
{
    auto* Engine = static_cast<WD::Engine*>(appstate);
    
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        SDL_Log("Quiting!");
        return SDL_APP_SUCCESS;
    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

int SDL_AppIterate(void* appstate)
{
    const WD::Engine* Engine = static_cast<WD::Engine*>(appstate);

    SDL_GL_SwapWindow(&Engine->GetWindow());

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate)
{
    delete static_cast<WD::Engine*>(appstate);
}
