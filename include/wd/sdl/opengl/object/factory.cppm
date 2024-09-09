module;

#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.Factory;

import wd.sdl.opengl.object.creator_node;
import wd.sdl.opengl.object.Storage;
import wd.utility.Constructors;

export namespace wd::sdl::opengl::object
{
    struct Factory : utility::NonMovable
    {
        auto GetStorage() const -> const Storage&;

        auto CreateShader(const GLchar* path, const GLenum type) -> Shader*;
        auto CreateProgram() -> shader::Program*;
        auto CreateBuffer(GLenum type) -> Buffer*;
        auto CreateVertexArray() -> vertex::Array*;

    private:
        Storage mStorage;
    };
}
