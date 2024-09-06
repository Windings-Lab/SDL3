module wd.engine.Engine;

namespace wd
{
    Engine::Engine(const int width, const int height)
        : NonMovable()
        , mGLContext(width, height)
    {
    }

    auto Engine::GetWindow() -> Window&
    {
        return mGLContext.GetWindow();
    }

    auto Engine::GetGLContext() -> gl::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
