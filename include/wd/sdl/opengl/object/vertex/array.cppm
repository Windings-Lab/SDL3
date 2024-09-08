export module wd.sdl.opengl.object.vertex.Array;

import wd.sdl.opengl.object.Object;
import wd.sdl.opengl.object.Buffer;

export namespace wd::sdl::opengl::object::vertex
{
    struct Array : public Object
    {
        Array(Buffer& vbo, Buffer& ebo);

        void ReadVBO();

        void Enable();
        void Disable();

        Buffer& VBO;
        Buffer& EBO;
    };
}
