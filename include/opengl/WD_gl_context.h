#pragma once

#include "opengl/shader/WD_gl_shader_container.h"
#include "engine/WD_window.h"

typedef struct SDL_GLContextState* SDL_GLContext;

namespace WD
{
    class Window;
}

namespace WD::GL
{
    class Shader;

    using buffer_container = std::vector<std::unique_ptr<class Buffer>>;
    using shader_program_container = std::vector<std::unique_ptr<class ShaderProgram>>;

    class Context
    {
    public:
        shader_program_container ShaderPrograms;

    public:
        Context(const int width, const int height);

        auto GetWindow() -> Window&;

        void Iterate();

        auto CreateShader(const GLchar* path, const GLenum type) -> const Shader*;
        void CreateShaderProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        Window mWindow;
        SDL_GLContext mValue = nullptr;
        boost::multi_index::shader_container mShaders;
        buffer_container mBuffers;
    };
}
