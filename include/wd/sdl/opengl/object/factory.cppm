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
        auto GetStorage() const noexcept -> const Storage&;

        auto CreateShader(const GLchar* path, const GLenum type) noexcept -> Shader*;
        auto CreateProgram() noexcept -> shader::Program*;
        auto CreateBuffer(GLenum type) noexcept -> Buffer*;
        auto CreateVertexArray() noexcept -> vertex::Array*;

        ~Factory() = default;

    private:
        Storage mStorage;
    };
}
