module;

#include <vector>
#include <memory>
#include "gl.h"

export module wd.sdl.opengl.Context;

export namespace wd::sdl
{
    class Window;
}

export typedef struct SDL_GLContextState* SDL_GLContext;

export namespace wd::sdl::opengl
{
    namespace object
    {
        using shader_container = std::vector<std::unique_ptr<struct Shader>>;
        using buffer_container = std::vector<std::unique_ptr<struct Buffer>>;
        namespace shader
        {
            using program_container = std::vector<std::unique_ptr<class Program>>;
        }
        namespace vertex
        {
            using array_container = std::vector<std::unique_ptr<struct Array>>;
        }
    }

    class Context
    {
    public:
        object::shader::program_container Programs;

    public:
        explicit Context(Window& window);

        auto GetWindow() -> Window&;

        void Iterate();

        auto CreateShader(const GLchar* path, const GLenum type) -> object::Shader*;
        void CreateProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        Window& mWindow;
        SDL_GLContext mValue = nullptr;
        object::shader_container mShaders;
        object::buffer_container mBuffers;
        object::vertex::array_container mVertexArrays;
    };
}
