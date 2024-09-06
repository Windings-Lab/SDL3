export module wd.engine.Engine;

import wd.gl.Context;
import wd.utility.Constructors;

export namespace wd
{
    class Window;

    class Engine : utility::NonMovable
    {
    public:
        auto GetWindow() -> Window&;
        auto GetGLContext() -> gl::Context&;

        Engine(const int width, const int height);
        ~Engine();

    private:
        gl::Context mGLContext;
    };
}
