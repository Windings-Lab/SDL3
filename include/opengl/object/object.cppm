module;

#include "opengl/gl.h"

export module wd.gl.object.Object;

import wd.utility.Constructors;

export namespace wd::gl
{
    struct Object : utility::NonMovable
    {
        Object() = delete;
        virtual ~Object() = 0;

        const GLuint ID;
        GLenum Type() const noexcept;

    protected:
        explicit Object(GLuint id, GLenum type);

    protected:
        GLenum mType;
    };
}
