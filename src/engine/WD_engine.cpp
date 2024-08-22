#include "engine/WD_engine.h"
#include "engine/WD_window.h"

#include "opengl/WD_gl_context.h"
#include "opengl/WD_gl_shader.h"


WD::Engine::Engine()
    : NonCopyable()
    , NonMovable()
{
}

WD::Window* WD::Engine::CreateWindow(int width, int height)
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

WD::GL::Context* WD::Engine::CreateGLContext(const Window& window)
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

WD::Window* WD::Engine::GetWindow() const
{
    return mWindow.get();
}

WD::GL::Context* WD::Engine::GetGLContext() const
{
    return mGLContext.get();
}

WD::Engine::~Engine()
{
    mGLContext.reset();
    mWindow.reset();
}
