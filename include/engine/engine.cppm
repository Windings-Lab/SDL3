module;

#include "opengl/WD_gl_context.h"

export module wd.engine.Engine;

import wd.utility.Constructors;

export namespace WD
{
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
