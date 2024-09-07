export module wd.gl.object.vertex.Array;

import wd.gl.object.Object;

export namespace wd::gl::object::vertex
{
    struct Array : public Object
    {
        Array();

        void Enable();
        void Disable();
    };
}
