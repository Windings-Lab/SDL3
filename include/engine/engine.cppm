module;

#include "opengl/WD_gl_context.h"
#include "utility/WD_constructors.h"

export module wd.engine.Engine;

export namespace WD
{
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
