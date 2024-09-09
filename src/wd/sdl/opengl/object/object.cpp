module;

#include <format>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Object;

namespace wd::sdl::opengl
{
    Object::~Object()
    {
    }

    GLenum Object::Type() const noexcept
    {
        return mType;
    }

    Object::Object(const GLuint id, const GLenum type)
        : ID(id)
        , mType(type)
    {
        const auto error = glGetError();
        if(error || ID == 0)
        {
            Assert(std::format("{0} is not created!", typeid(*this).name()));
        }
    }
}
