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
        explicit Context(Window* window);

        void Iterate();

        void CreateShaderProgram();
        void UpdateViewport(int width, int height);

        std::vector<std::unique_ptr<class ShaderProgram>> ShaderPrograms;

        ~Context();

    private:
        SDL_GLContext mValue = nullptr;
        Window* mWindow;

        std::vector<class Buffer> mBuffers;
    };
}
