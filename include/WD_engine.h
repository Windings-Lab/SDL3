#pragma once

#include "WD_gl_pipeline.h"
#include "utility/WD_constructors.h"

class SDL_Window;
typedef struct SDL_GLContextState *SDL_GLContext;

namespace WD
{
    // Class for handling Window and OpenGL Context
    class Engine : Utillity::NonCopyable, Utillity::NonMovable
    {
    public:
        Engine(SDL_Window* window, SDL_GLContext context);
        ~Engine();
        Engine(const Engine& other) = delete;
        Engine& operator=(const Engine& other) = delete;
        Engine(Engine&& other) = delete;
        Engine& operator=(Engine&& other) = delete;

        SDL_Window* GetWindow() const;
        
    public:
        ShaderProgram ShaderProgram = WD::ShaderProgram();
        
    private:
        SDL_Window*     mWindow = nullptr;
        SDL_GLContext   mContext = nullptr;

    };
}
