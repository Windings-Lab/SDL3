module;

#include <memory>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Factory;

namespace wd::sdl::opengl::object
{
    auto Factory::GetStorage() -> const Storage&
    {
        return mStorage;
    }

    auto Factory::CreateShader(const GLchar* path, const GLenum type) -> Shader*
    {
        auto shader = std::make_unique<Shader>(path, type);
        shader->Compile();
        const auto shaderPtr = shader.get();
        mStorage.Shaders.emplace_back(std::move(shader));

        return shaderPtr;
    }

    auto Factory::CreateProgram() -> shader::Program*
    {
        auto program = std::make_unique<shader::Program>();
        const auto programPtr = program.get();
        mStorage.Programs.emplace_back(std::move(program));

        return programPtr;
    }

    auto Factory::CreateBuffer(GLenum type) -> Buffer*
    {
        auto buffer = std::make_unique<Buffer>(type);
        const auto bufferPtr = buffer.get();
        mStorage.Buffers.emplace_back(std::move(buffer));

        return bufferPtr;
    }

    auto Factory::CreateVertexArray(Buffer& vbo, Buffer& ebo) -> vertex::Array*
    {
        auto vertexArray = std::make_unique<vertex::Array>(vbo, ebo);
        const auto vertexArrayPtr = vertexArray.get();
        mStorage.VertexArrays.emplace_back(std::move(vertexArray));

        return vertexArrayPtr;
    }
}
