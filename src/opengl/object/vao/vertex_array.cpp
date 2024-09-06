module;

#include "opengl/gl.h"

module wd.gl.object.VertexArray;

namespace wd::gl
{
    VertexArray::VertexArray()
        : Object([]
        {
            GLuint id;
            glGenVertexArrays(1, &id);
            return id;
        }(), GL_VERTEX_ARRAY)
    {
        glBindVertexArray(ID);
    }

    void VertexArray::Enable()
    {
        glEnableVertexArrayAttrib(ID, 0);
    }

    void VertexArray::Disable()
    {
        glDisableVertexArrayAttrib(ID, 0);
    }
}
