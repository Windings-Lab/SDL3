#pragma once

#include "utility/WD_constructors.h"

struct SDL_Window;
typedef struct SDL_GLContextState *SDL_GLContext;

namespace WD
{
    namespace GL
    {
        class Buffer;
    }

    // Class for handling Window and OpenGL Context
    class Engine : Utillity::NonCopyable, Utillity::NonMovable
    {
    public:
        SDL_Window* GetWindow() const;

        std::vector<std::unique_ptr<class ShaderProgram>> ShaderPrograms;
        std::vector<GL::Buffer> Buffers;

        Engine(SDL_Window* window, SDL_GLContext context);
        ~Engine();

    private:
        SDL_Window*     mWindow = nullptr;
        SDL_GLContext   mContext = nullptr;
    };
}
