#pragma once

namespace WD::GL
{
    class Buffer : Utillity::NonMovable
    {
    public:
        bool BindTo(const GLenum target);
        bool BufferData(const void* data, const size_t size, const GLenum usage);

        GLuint ID() const;
        GLenum Target() const;

    public:
        Buffer();
        ~Buffer();

    private:
        GLuint mID;
        GLenum mTarget;
    };
}
