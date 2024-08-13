#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "glad/gl.h"

#include "WD_engine.h"
#include "WD_gl_pipeline.h"
#include "keyboard/WD_keyboard.h"

int SDL_AppInit(void **appstate, int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_SetError("SDL failed to initialize!");
        SDL_LogError(0, "%s", SDL_GetError());

        return SDL_APP_FAILURE;
    }

    // OpenGL Version 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // All core and deprecated OPENGL function are available
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Double buffer for window swap
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    constexpr int Width = 800;
    constexpr int Height = 600;
    auto* Window = SDL_CreateWindow("Hello SDL and OpenGL", Width, Height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
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

    // GLAD initialization
    if(!gladLoadGL(SDL_GL_GetProcAddress))
    {
        SDL_DestroyWindow(Window);
        SDL_SetError("GLAD failed to initialize!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    // OpenGL Viewport dimensions
    glViewport(0, 0, Width, Height);

    // Creating an instance for an SDL appstate
    auto* Engine = new WD::Engine(Window, Context);
    *appstate = static_cast<void*>(Engine);
    
    Engine->ShaderProgram = WD::CreateShaderProgram();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5.f);

    return SDL_APP_CONTINUE;
}

int SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    const auto* Engine = static_cast<WD::Engine*>(appstate);
    
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        {
            return WD::Keyboard::Handle_Input(event->key.key);
        }
    case SDL_EVENT_QUIT:
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }
    case SDL_EVENT_WINDOW_RESIZED:
        {
            int Width = 0;
            int Height = 0;
            SDL_GetWindowSize(Engine->GetWindow(), &Width, &Height);
            glViewport(0, 0, Width, Height);

            SDL_Log("Window resized: %dx%d", Width, Height);
            break;
        }
    default:
        {
            break;
        }
    }

    return SDL_APP_CONTINUE;
}

int SDL_AppIterate(void *appstate)
{
    const WD::Engine* Engine = static_cast<WD::Engine*>(appstate);

    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Engine->ShaderProgram.ID);
    glBindVertexArray(Engine->ShaderProgram.VAO);
    glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
    
    SDL_GL_SwapWindow(Engine->GetWindow());
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<WD::Engine*>(appstate);
}
