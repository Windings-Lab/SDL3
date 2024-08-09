#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include "SDL3/SDL.h"

constexpr int   WIDTH = 800;
constexpr int   HEIGHT = 600;
SDL_Window*     WINDOW = nullptr;

SDL_GLContext   OPENGL_CONTEXT = nullptr;

int SDL_AppInit(void **appstate, int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL failed to initialize!");

        return SDL_APP_FAILURE;
    }

    // Version 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // All core and deprecated OPENGL function are available
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    WINDOW = SDL_CreateWindow("Hello SDL and OpenGL", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if(!WINDOW)
    {
        SDL_Log("Window failed to create!");

        return SDL_APP_FAILURE;
    }

    // OpenGL Context is a OpenGL state machine
    OPENGL_CONTEXT = SDL_GL_CreateContext(WINDOW);
    if(!OPENGL_CONTEXT)
    {
        SDL_Log("OpenGL Context failed to create!");

        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

int SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        SDL_Log("Quiting!");
        return SDL_APP_SUCCESS;
    default: ;
    }

    return SDL_APP_CONTINUE;
}

int SDL_AppIterate(void *appstate)
{
    SDL_GL_SwapWindow(WINDOW);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    if(WINDOW)
    {
        SDL_DestroyWindow(WINDOW);
    }
}
