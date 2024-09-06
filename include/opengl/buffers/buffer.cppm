module;

#include "opengl/glad/gl.h"

export module wd.opengl.Buffer;

import wd.utility.Constructors;

export namespace wd::gl
{
    class Buffer : utility::NonMovable
    {
    public:
        void BindTo(const GLenum type);
        void BufferData(const void* data, const size_t size, const GLenum usage);

        GLuint ID() const;
        GLenum Target() const;

    public:
        Buffer();
        ~Buffer();

    private:
        GLuint mID;
        GLenum mType;
    };
}
