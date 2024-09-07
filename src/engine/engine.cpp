module wd.engine.Engine;

namespace wd
{
    Engine::Engine(const int width, const int height)
        : NonMovable()
        , mWindow(width, height)
        , mGLContext(mWindow)
    {
    }

    auto Engine::GetWindow() -> Window&
    {
        return mWindow;
    }

    auto Engine::GetGLContext() -> gl::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
