#include "engine/WD_engine.h"
#include "engine/WD_window.h"

#include "opengl/WD_gl_context.h"

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
