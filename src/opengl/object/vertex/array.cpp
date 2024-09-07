module;

#include "opengl/gl.h"

module wd.gl.object.vertex.Array;

namespace wd::gl::object::vertex
{
    Array::Array()
        : Object([]
        {
            GLuint id;
            glGenVertexArrays(1, &id);
            return id;
        }(), GL_VERTEX_ARRAY)
    {
        glBindVertexArray(ID);
    }

    void Array::Enable()
    {
        glEnableVertexArrayAttrib(ID, 0);
    }

    void Array::Disable()
    {
        glDisableVertexArrayAttrib(ID, 0);
    }
}
