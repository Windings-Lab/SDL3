module;

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.vertex.Array;

import wd.sdl.opengl.object.Buffer;

namespace wd::sdl::opengl::object::vertex
{
    Array::Array(Buffer& vbo, Buffer& ebo)
        : Object([]
        {
            GLuint id;
            glGenVertexArrays(1, &id);
            return id;
        }(), GL_VERTEX_ARRAY)
        , VBO(vbo)
        , EBO(ebo)
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
