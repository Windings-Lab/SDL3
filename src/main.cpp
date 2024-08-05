#include <SDL3/SDL.h>

constexpr int   WIDTH = 800;
constexpr int   HEIGHT = 600;
SDL_Window*     WINDOW = nullptr;

SDL_GLContext   OPENGL_CONTEXT = nullptr;

bool            LOOP_ENABLED = true;

bool InitializeSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL failed to initialize!");

        return false;
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

        return false;
    }

    // OpenGL Context is a OpenGL state machine
    OPENGL_CONTEXT = SDL_GL_CreateContext(WINDOW);
    if(!OPENGL_CONTEXT)
    {
        SDL_Log("OpenGL Context failed to create!");

        return false;
    }

    return true;
}

void Handler()
{
    SDL_Event e;

    bool bEventDetected = SDL_PollEvent(&e) == SDL_TRUE;
    while (bEventDetected)
    {
        switch (e.type)
        {
        case SDL_EVENT_QUIT:
            SDL_Log("Quiting!");
            LOOP_ENABLED = false;
            break;
        default: ;
        }

        bEventDetected = SDL_PollEvent(&e) == SDL_TRUE;
    }
}

void Loop()
{
    while (LOOP_ENABLED)
    {
        Handler();

        SDL_GL_SwapWindow(WINDOW);
    }
}

void CleanUp()
{
    if(WINDOW)
    {
        SDL_DestroyWindow(WINDOW);
    }

    SDL_Quit();
}

int main(int argc, char* argv[])
{    
    if(InitializeSDL())
    {
        Loop();
    }

    CleanUp();
    
    return 0;
}