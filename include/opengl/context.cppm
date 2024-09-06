module;

#include <vector>
#include <memory>
#include "opengl/glad/gl.h"

export module wd.gl.Context;

import wd.gl.shader.Container;
import wd.gl.shader.Program;
import wd.engine.Window;

export typedef struct SDL_GLContextState* SDL_GLContext;

export namespace wd::gl
{
    using buffer_container = std::vector<std::unique_ptr<class Buffer>>;
    using shader_program_container = std::vector<std::unique_ptr<ShaderProgram>>;

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
        shader_container mShaders;
        buffer_container mBuffers;
    };
}
