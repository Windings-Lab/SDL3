module;

#include <format>
#include "opengl/glad/gl.h"

module wd.opengl.Buffer;

import wd.engine.Log;

namespace wd::gl
{
    Buffer::Buffer()
        : mID(0)
        , mType(0)
    {
        glGenBuffers(1, &mID);
        const auto error = glGetError();
        if (error || mID == 0)
        {
            LogError(std::format("Failed to create buffer"), true);
        }
    }

    GLuint Buffer::ID() const
    {
        return mID;
    }

    GLenum Buffer::Target() const
    {
        return mType;
    }

    void Buffer::BindTo(const GLenum type)
    {
        glBindBuffer(type, mID);
        if (const auto error = glGetError())
        {
            LogError(std::format("Failed to bind buffer"), true);
        }

        mType = type;
    }

    void Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(mID, size, data, usage);
        if (const auto error = glGetError())
        {
            LogError(std::format("Failed to buffer data"), true);
        }
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &mID);
    }
}
