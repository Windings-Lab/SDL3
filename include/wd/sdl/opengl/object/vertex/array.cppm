export module wd.sdl.opengl.object.vertex.Array;

import wd.sdl.opengl.object.Object;
import wd.sdl.opengl.object.Buffer;

export namespace wd::sdl::opengl::object::vertex
{
    struct Array : public Object
    {
        Array();

        void ReadVBO() noexcept;

        void Enable() noexcept;
        void Disable() noexcept;

        Buffer VBO;
        Buffer EBO;
    };
}
