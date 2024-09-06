module;

#include <format>
#include "opengl/gl.h"

module wd.gl.object.Object;

import wd.engine.Log;

namespace wd::gl
{
    Object::~Object()
    {
    }

    Object::Object(const GLuint id, const GLenum type)
        : ID(id)
        , Type(type)
    {
        const auto error = glGetError();
        if(error || ID == 0)
        {
            LogError(std::format("{0} is not created!", typeid(*this).name()), true);
        }
    }
}
