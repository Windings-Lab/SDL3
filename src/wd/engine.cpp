module wd.Engine;

namespace wd
{
    Engine::Engine(const int width, const int height)
        : NonMovable()
        , mWindow(width, height)
        , mGLContext(mWindow)
    {
    }

    auto Engine::GetWindow() -> sdl::Window&
    {
        return mWindow;
    }

    auto Engine::GetGLContext() -> sdl::opengl::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
