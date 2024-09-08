#define SDL_MAIN_USE_CALLBACKS
#include <SDL.h>
#include <SDL_main.h>

#include "wd/sdl/opengl/gl.h"

import wd;

void DoSomething()
{

}

void CreateShaderProgram(wd::sdl::opengl::Context& glContext)
{
    glContext.CreateProgram();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5.f);

    auto shaderProgram = glContext.Programs[0].get();
    shaderProgram->Use();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        wd::sdl::LogError("SDL failed to initialize!");

        return SDL_APP_FAILURE;
    }

    constexpr auto Width = 800;
    constexpr auto Height = 600;

    wd::Engine* Engine = new wd::Engine(Width, Height);
    *appstate = static_cast<void*>(Engine);

    CreateShaderProgram(Engine->GetGLContext());
    DoSomething();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        {
            return wd::sdl::Handle_Input(event->key.key);
        }
    case SDL_EVENT_QUIT:
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }
    case SDL_EVENT_WINDOW_RESIZED:
        {
            auto& window = Engine->GetWindow();
            window.Update();
            const auto width = window.Width();
            const auto height = window.Height();
            Engine->GetGLContext().UpdateViewport(width, height);

            SDL_Log("Window resized: %dx%d", width, height);
            break;
        }
    default:
        {
            break;
        }
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto* Engine = static_cast<wd::Engine*>(appstate);

    Engine->GetGLContext().Iterate();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<wd::Engine*>(appstate);
}
