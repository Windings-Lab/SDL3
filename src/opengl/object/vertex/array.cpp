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
        , VBO(GL_ARRAY_BUFFER)
        , EBO(GL_ELEMENT_ARRAY_BUFFER)
    {
        glBindVertexArray(ID);
    }

    void Array::ReadVBO()
    {
        constexpr auto axes = 3;
        glVertexAttribPointer(0, axes, GL_DOUBLE, GL_FALSE, axes * sizeof(double), nullptr);
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
