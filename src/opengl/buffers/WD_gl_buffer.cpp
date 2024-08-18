#include "opengl/buffers/WD_gl_buffer.h"

namespace WD::GL
{
    Buffer::Buffer()
        : ID(0)
        , Target(0)
    {
        glGenBuffers(1, const_cast<GLuint*>(&ID));
        if (ID == 0) throw glGetError();
    }

    Buffer::Buffer(Buffer&& other) noexcept : ID(other.ID), Target(other.Target)
    {
        const_cast<GLuint&>(other.ID) = 0;
        const_cast<GLenum&>(other.Target) = 0;
    }

    Buffer& Buffer::operator=(Buffer&& other) noexcept
    {
        if(this != &other)
        {
            Buffer tmp(std::move(other));
            swap(tmp);
        }

        return *this;
    }

    Buffer::~Buffer()
    {
        if(ID == 0) return;

        glDeleteBuffers(1, &ID);
    }

    bool Buffer::BindTo(const GLenum target)
    {
        glBindBuffer(target, ID);
        if(glGetError() != GL_NO_ERROR) return false;

        Target = target;
        return true;
    }

    bool Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(ID, size, data, usage);
        if(glGetError() != GL_NO_ERROR) return false;

        return true;
    }

    GLenum Buffer::GetTarget() const
    {
        return Target;
    }

    void Buffer::swap(Buffer& other) noexcept
    {
        using std::swap;

        swap(const_cast<GLuint&>(ID), const_cast<GLuint&>(other.ID));
        swap(Target, other.Target);
    }
}
