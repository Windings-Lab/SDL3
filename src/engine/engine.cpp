module wd.engine.Engine;

namespace WD
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

    auto Engine::GetGLContext() -> GL::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
