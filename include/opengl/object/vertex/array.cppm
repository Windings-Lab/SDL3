export module wd.gl.object.vertex.Array;

import wd.gl.object.Object;
import wd.gl.object.Buffer;

export namespace wd::gl::object::vertex
{
    struct Array : public Object
    {
        Array();

        void ReadVBO();

        void Enable();
        void Disable();

        Buffer VBO;
        Buffer EBO;
    };
}
