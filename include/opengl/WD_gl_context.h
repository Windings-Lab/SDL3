#pragma once

typedef struct SDL_GLContextState* SDL_GLContext;

namespace WD
{
    class Window;
}

namespace WD::GL
{
    class Context
    {
    public:
        std::vector<std::unique_ptr<class ShaderProgram>> ShaderPrograms;

    public:
        explicit Context(Window* window);

        void Iterate();

        void CreateShaderProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        SDL_GLContext mValue = nullptr;
        Window* mWindow;

        std::vector<class Buffer> mBuffers;
    };
}
