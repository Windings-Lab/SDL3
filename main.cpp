#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"
#include "SDL3/SDL.h"

#include "engine/WD_engine.h"
#include "engine/keyboard/WD_keyboard.h"
#include "engine/WD_window.h"

#include "opengl/WD_gl_shader.h"
#include "opengl/WD_gl_context.h"

void DoSomething()
{

}

void CreateShaderProgram(WD::GL::Context* glContext)
{
    glContext->CreateShaderProgram();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5.f);

    glContext->ShaderPrograms[0]->Use();
}

int SDL_AppInit(void **appstate, int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        WD::LogError("SDL failed to initialize!");

        return SDL_APP_FAILURE;
    }

    WD::Engine* Engine = new WD::Engine();
    *appstate = static_cast<void*>(Engine);

    constexpr int Height = 600;
    constexpr int Width = 800;
    const WD::Window* Window = Engine->CreateWindow(Width, Height);
    if(!Window)
    {
        return SDL_APP_FAILURE;
    }

    WD::GL::Context* glContext = Engine->CreateGLContext(*Window);
    if(!glContext)
    {
        return SDL_APP_FAILURE;
    }

    CreateShaderProgram(glContext);
    DoSomething();

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
            WD::Window* window = Engine->GetWindow();
            window->Update();
            const int width = window->Width();
            const int height = window->Height();
            Engine->GetGLContext()->UpdateViewport(width, height);

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

int SDL_AppIterate(void *appstate)
{
    WD::Engine* Engine = static_cast<WD::Engine*>(appstate);

    Engine->GetGLContext()->Iterate();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<WD::Engine*>(appstate);
}
