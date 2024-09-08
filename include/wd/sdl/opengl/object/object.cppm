module;

#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.Object;

export import wd.sdl.Log;
import wd.utility.Constructors;

export namespace wd::sdl::opengl
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
