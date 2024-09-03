#pragma once

#include <boost/multi_index_container.hpp>
#include "opengl/glad/gl.h"

import wd.opengl.shader.Container;
import wd.engine.Window;

typedef struct SDL_GLContextState* SDL_GLContext;

namespace WD::GL
{
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
        shader_container mShaders;
        buffer_container mBuffers;
    };
}
