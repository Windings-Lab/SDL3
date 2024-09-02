#pragma once

#include "opengl/WD_gl_context.h"

namespace WD
{
    namespace GL
    {
        class Context;
    }

    class Engine : Utillity::NonMovable
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
