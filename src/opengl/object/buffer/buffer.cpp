module;

#include <format>
#include "opengl/gl.h"

module wd.gl.object.Buffer;

import wd.engine.Log;

namespace wd::gl
{
    Buffer::Buffer(const GLenum type) : Object([]
    {
        GLuint id;
        glGenBuffers(1, &id);
        return id;
    }(), type)
    {
        glBindBuffer(type, ID);
        if (const auto error = glGetError())
        {
            LogError(std::format("Failed to bind buffer"), true);
        }
    }

    void Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(ID, size, data, usage);
        if (const auto error = glGetError())
        {
            LogError(std::format("Failed to buffer data"), true);
        }
    }

    void Buffer::Unbind()
    {
        glBindBuffer(mType, 0);
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &ID);
    }
}
