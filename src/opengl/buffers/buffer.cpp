module;

#include <format>
#include "opengl/glad/gl.h"

module wd.opengl.Buffer;

import wd.engine.Log;

namespace WD::GL
{
    Buffer::Buffer()
        : mID(0)
        , mTarget(0)
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
        return mTarget;
    }

    bool Buffer::BindTo(const GLenum target)
    {
        glBindBuffer(target, mID);
        if(glGetError() != GL_NO_ERROR) return false;

        mTarget = target;
        return true;
    }

    bool Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(mID, size, data, usage);
        if(glGetError() != GL_NO_ERROR) return false;

        return true;
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &mID);
    }
}
