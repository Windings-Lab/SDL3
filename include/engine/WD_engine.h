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
        Window* GetWindow() const;
        GL::Context* GetGLContext() const;

        Window* CreateWindow(int width, int height);
        GL::Context* CreateGLContext(const Window& window);

        Engine();
        ~Engine();

    private:
        WindowPtr mWindow;
        ContextPtr mGLContext;
    };
}
