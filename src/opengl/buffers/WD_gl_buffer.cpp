#include "opengl/buffers/WD_gl_buffer.h"

namespace WD::GL
{
    Buffer::Buffer()
        : ID(0)
        , Target(0)
    {
        glGenBuffers(1, &ID);
        if (ID == 0) throw glGetError();
    }

    GLuint Buffer::GetID() const
    {
        return ID;
    }

    GLenum Buffer::GetTarget() const
    {
        return Target;
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

    Buffer::Buffer(Buffer&& other) noexcept : ID(other.ID), Target(other.Target)
    {
        other.ID = 0;
        other.Target = 0;
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

    void Buffer::swap(Buffer& other) noexcept
    {
        using std::swap;

        swap(ID, other.ID);
        swap(Target, other.Target);
    }
}
