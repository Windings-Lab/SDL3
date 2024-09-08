module;

#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.Factory;

export import wd.sdl.opengl.object.Storage;
import wd.utility.Constructors;

export namespace wd::sdl::opengl::object
{
    struct Factory : utility::NonMovable
    {
        auto GetStorage() -> const Storage&;

        auto CreateShader(const GLchar* path, const GLenum type) -> Shader*;
        auto CreateProgram() -> shader::Program*;
        auto CreateBuffer(GLenum type) -> Buffer*;
        auto CreateVertexArray(Buffer& vbo, Buffer& ebo) -> vertex::Array*;

    private:
        Storage mStorage;
    };
}
