module;

#include "opengl/glad/gl.h"

export module wd.opengl.Buffer;

import wd.utility.Constructors;

export namespace WD::GL
{
    class Buffer : Utility::NonMovable
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
