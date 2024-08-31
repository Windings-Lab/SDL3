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

    auto Engine::CreateWindow(int width, int height) -> Window*
    {
        if(mWindow)
        {
            LogError(std::format("Window already created!"));
            return mWindow.get();
        }

        try
        {
            mWindow = std::make_unique<Window>(width, height);
        }
        catch (std::runtime_error& e)
        {
            return nullptr;
        }

        return mWindow.get();
    }

    auto Engine::CreateGLContext(const Window& window) -> GL::Context*
    {
        if(mGLContext)
        {
            LogError(std::format("OpenGL Context already created!"));
            return mGLContext.get();
        }

        if(&window != mWindow.get())
        {
            if(!mWindow)
            {
                LogError(std::format("Engine window not created! Weird behaviour"));
                return nullptr;
            }

            LogError(std::format("Engine window and provided window are not equal! Weird behaviour"));
            return nullptr;
        }

        try
        {
            mGLContext = std::make_unique<GL::Context>(mWindow.get());
        }
        catch (std::runtime_error& e)
        {
            return nullptr;
        }

        return mGLContext.get();
    }

    auto Engine::GetWindow() const -> Window*
    {
        return mWindow.get();
    }

    auto Engine::GetGLContext() const -> GL::Context*
    {
        return mGLContext.get();
    }

    Engine::~Engine()
    {
        mGLContext.reset();
        mWindow.reset();
    }
}
