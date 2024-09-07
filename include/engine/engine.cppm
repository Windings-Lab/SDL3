export module wd.engine.Engine;

import wd.gl.Context;
import wd.engine.Window;
import wd.utility.Constructors;

export namespace wd
{
    class Engine : utility::NonMovable
    {
    public:
        auto GetWindow() -> Window&;
        auto GetGLContext() -> gl::Context&;

        Engine(const int width, const int height);
        ~Engine();

    private:
        Window mWindow;
        gl::Context mGLContext;
    };
}
