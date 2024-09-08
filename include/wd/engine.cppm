export module wd.Engine;

import wd.sdl.opengl.Context;
import wd.sdl.Window;
import wd.utility.Constructors;

export namespace wd
{
    class Engine : utility::NonMovable
    {
    public:
        auto GetWindow() -> sdl::Window&;
        auto GetGLContext() -> sdl::opengl::Context&;

        Engine(const int width, const int height);
        ~Engine();

    private:
        sdl::Window mWindow;
        sdl::opengl::Context mGLContext;
    };
}
