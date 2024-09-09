module;

#include <format>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Buffer;

namespace wd::sdl::opengl::object
{
    Buffer::Buffer(const GLenum type) : Object([]
    {
        GLuint id;
        glGenBuffers(1, &id);
        return id;
    }(), type)
    {
    }

    void Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(ID, size, data, usage);
        if (const auto error = glGetError())
        {
            Assert(std::format("Failed to buffer data"));
        }
    }

    void Buffer::Bind()
    {
        glBindBuffer(mType, ID);
        if (const auto error = glGetError())
        {
            Assert(std::format("Failed to bind buffer"));
        }
    }

    void Buffer::Unbind()
    {
        glBindBuffer(mType, 0);
        if (const auto error = glGetError())
        {
            Assert(std::format("Failed to unbind buffer"));
        }
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &ID);
    }
}
