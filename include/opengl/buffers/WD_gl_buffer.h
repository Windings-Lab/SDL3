#pragma once

#include "utility/WD_constructors.h"

namespace WD::GL
{
    class Buffer : Utillity::NonCopyable
    {
    public:
        Buffer();
        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;
        ~Buffer();

        const GLuint ID;

    public:
        bool BindTo(GLenum target);
        bool BufferData(const void* data, size_t size, GLenum usage);

        GLenum GetTarget() const;

    private:
        void swap(Buffer& other) noexcept;

    private:
        GLenum Target;
    };
}
