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
    namespace object
    {
        using buffer_container = std::vector<std::unique_ptr<struct Buffer>>;
        namespace shader
        {
            using container = std::vector<std::unique_ptr<class Program>>;
        }
        namespace vertex
        {
            using container = std::vector<std::unique_ptr<struct Array>>;
        }
    }

    class Context
    {
    public:
        object::shader::container Programs;

    public:
        Context(const int width, const int height);

        auto GetWindow() -> Window&;

        void Iterate();

        auto CreateShader(const GLchar* path, const GLenum type) -> const object::Shader*;
        void CreateProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        Window mWindow;
        SDL_GLContext mValue = nullptr;
        shader_container mShaders;
        object::buffer_container mBuffers;
        object::vertex::container mVertexArrays;
    };
}
