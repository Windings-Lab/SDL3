module;

#include <vector>
#include <memory>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include "gl.h"

export module wd.gl.Context;

import wd.gl.object.shader.Container;
import wd.engine.Window;

export typedef struct SDL_GLContextState* SDL_GLContext;

export namespace wd::gl
{
    using program_container = std::vector<std::unique_ptr<class Program>>;
    using buffer_container = std::vector<std::unique_ptr<struct Buffer>>;
    using vao_container = std::vector<std::unique_ptr<struct VertexArray>>;

    class Context
    {
    public:
        program_container Programs;

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
        vao_container mVertexArrays;
    };
}
