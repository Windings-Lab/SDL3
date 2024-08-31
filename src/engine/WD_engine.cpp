#include "engine/WD_engine.h"
#include "engine/WD_window.h"

#include "opengl/WD_gl_context.h"
#include "opengl/WD_gl_shader.h"

namespace WD
{
    Engine::Engine()
        : NonCopyable()
        , NonMovable()
    {
    }

    auto Engine::CreateWindow(const int width, const int height) -> Window&
    {
        if(mWindow)
        {
            LogError(std::format("Window already created!"), true);
        }

        mWindow = std::make_unique<Window>(width, height);

        return *mWindow;
    }

    auto Engine::CreateGLContext(const Window& window) -> GL::Context&
    {
        if(mGLContext)
        {
            LogError(std::format("OpenGL Context already created!"));
            return *mGLContext;
        }

        if(&window != mWindow.get())
        {
            if(!mWindow)
            {
                LogError(std::format("Engine window not created! Weird behaviour"), true);
            }

            LogError(std::format("Engine window and provided window are not equal! Weird behaviour"), true);
        }

        mGLContext = std::make_unique<GL::Context>(*mWindow);

        return *mGLContext;
    }

    auto Engine::GetWindow() -> Window&
    {
        return *mWindow;
    }

    auto Engine::GetGLContext() -> GL::Context&
    {
        return *mGLContext;
    }

    Engine::~Engine()
    {
        mGLContext.reset();
        mWindow.reset();
    }
}
