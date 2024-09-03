module;

#include <boost/multi_index_container.hpp>

export module wd.engine.Engine;

import wd.opengl.Context;
import wd.utility.Constructors;

export namespace WD
{
    class Window;

    class Engine : Utility::NonMovable
    {
    public:
        auto GetWindow() -> Window&;
        auto GetGLContext() -> GL::Context&;

        Engine(const int width, const int height);
        ~Engine();

    private:
        GL::Context mGLContext;
    };
}
