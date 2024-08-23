#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"
#include "SDL3/SDL.h"

#include "engine/WD_engine.h"
#include "engine/keyboard/WD_keyboard.h"
#include "engine/WD_window.h"

#include "opengl/WD_gl_shader.h"
#include "opengl/WD_gl_context.h"

#include <chrono>
#include "engine/math/WD_math.h"

double cpu_time(void (*func)())
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> total = end - start;

    return total.count();
}

void DoSomething()
{
    constexpr double clock_rate = 3910000000;
    const double cpu_time1 = cpu_time(WD::Math::DoSomething);
    const double cpu_time2 = cpu_time(WD::Math::DoSomethingRef);

    int ret = 5;
}

void CreateShaderProgram(WD::GL::Context* glContext)
{
    glContext->CreateShaderProgram();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5.f);

    glContext->ShaderPrograms[0]->Use();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
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
#undef CreateWindow
    const WD::Window* Window = Engine->CreateWindow(Width, Height);
#define CreateWindow __MINGW_NAME_AW(CreateWindow)
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

SDL_AppResult SDL_AppEvent(void *appstate, const SDL_Event *event)
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

SDL_AppResult SDL_AppIterate(void *appstate)
{
    WD::Engine* Engine = static_cast<WD::Engine*>(appstate);

    Engine->GetGLContext()->Iterate();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<WD::Engine*>(appstate);
}
