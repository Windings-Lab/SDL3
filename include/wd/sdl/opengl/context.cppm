module;

#include <vector>
#include <memory>
#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.Context;

export import wd.sdl.opengl.object;
export import wd.sdl.Window;
import wd.sdl.Log;
import wd.utility.Constructors;

export typedef struct SDL_GLContextState* SDL_GLContext;

export namespace wd::sdl::opengl
{
    namespace object
    {
        using shader_container = std::vector<std::unique_ptr<Shader>>;
        using buffer_container = std::vector<std::unique_ptr<Buffer>>;
        namespace shader
        {
            using program_container = std::vector<std::unique_ptr<Program>>;
        }
        namespace vertex
        {
            using array_container = std::vector<std::unique_ptr<Array>>;
        }
    }

    class Context : utility::NonMovable
    {
    public:
        object::shader::program_container Programs;

    public:
        explicit Context(const int width, const int height);

        auto GetWindow() -> Window&;

        void Iterate();

        auto CreateShader(const GLchar* path, const GLenum type) -> object::Shader*;
        void CreateProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        Window mWindow;
        SDL_GLContext mValue = nullptr;
        object::shader_container mShaders;
        object::buffer_container mBuffers;
        object::vertex::array_container mVertexArrays;
    };
}
