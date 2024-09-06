export module wd.gl.object.VertexArray;

import wd.gl.object.Object;

export namespace wd::gl
{
    struct VertexArray : public Object
    {
        VertexArray();

        void Enable();
        void Disable();
    };
}
