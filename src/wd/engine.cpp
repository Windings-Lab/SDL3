module;

#include <SDL_init.h>
#include <format>
#include <SDL_log.h>

#include "wd/sdl/opengl/gl.h"

module wd.Engine;

namespace
{
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
}

namespace wd
{
    Engine::Engine(const int width, const int height)
        : NonMovable()
        , mGLContext(width, height)
    {

    }

    auto Engine::OnInit() -> SDL_AppResult
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            sdl::LogError(std::format("SDL failed to initialize!"));
            return SDL_APP_FAILURE;
        }

        CreateShaderProgram(mGLContext);

        return SDL_APP_CONTINUE;
    }

    auto Engine::OnEvent(const SDL_Event* event) -> SDL_AppResult
    {
        switch (event->type)
        {
        case SDL_EVENT_KEY_DOWN:
            {
                return sdl::Handle_Input(event->key.key);
            }
        case SDL_EVENT_QUIT:
            {
                SDL_Log("Quiting!");
                return SDL_APP_SUCCESS;
            }
        case SDL_EVENT_WINDOW_RESIZED:
            {
                auto& window = GetWindow();
                window.Update();
                const auto width = window.Width();
                const auto height = window.Height();
                GetGLContext().UpdateViewport(width, height);

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

    auto Engine::OnIterate() -> SDL_AppResult
    {
        GetGLContext().Iterate();
        return SDL_APP_CONTINUE;
    }

    auto Engine::GetWindow() -> sdl::Window&
    {
        return mGLContext.GetWindow();
    }

    auto Engine::GetGLContext() -> sdl::opengl::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
