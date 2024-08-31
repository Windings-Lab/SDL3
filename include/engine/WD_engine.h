#pragma once

#include "utility/WD_constructors.h"

namespace WD
{
    namespace GL
    {
        class Context;
    }

    using WindowPtr = std::unique_ptr<class Window>;
    using ContextPtr = std::unique_ptr<GL::Context>;

    // Class for handling Window and OpenGL Context
    class Engine : Utillity::NonCopyable, Utillity::NonMovable
    {
    public:
        auto GetWindow() -> Window&;
        auto GetGLContext() -> GL::Context&;

        auto CreateWindow(int width, int height) -> Window&;
        auto CreateGLContext(const Window& window) -> GL::Context&;

        Engine();
        ~Engine();

    private:
        WindowPtr mWindow;
        ContextPtr mGLContext;
    };
}
