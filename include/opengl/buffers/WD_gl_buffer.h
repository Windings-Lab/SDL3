#pragma once

#include "utility/WD_constructors.h"

namespace WD::GL
{
    class Buffer : Utillity::NonCopyable
    {
    public:
        bool BindTo(GLenum target);
        bool BufferData(const void* data, size_t size, GLenum usage);

        GLuint GetID() const;
        GLenum GetTarget() const;

    public:
        Buffer();
        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;
        ~Buffer();

    private:
        void swap(Buffer& other) noexcept;
        GLuint ID;
        GLenum Target;
    };
}
