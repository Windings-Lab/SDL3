#pragma once

#include "utility/WD_constructors.h"

namespace WD::GL
{
    class Buffer : Utillity::NonCopyable
    {
    public:
        bool BindTo(const GLenum target);
        bool BufferData(const void* data, const size_t size, const GLenum usage);

        GLuint ID() const;
        GLenum Target() const;

    public:
        Buffer();
        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;
        ~Buffer();

    private:
        void swap(Buffer& other) noexcept;
        GLuint mID;
        GLenum mTarget;
    };
}
