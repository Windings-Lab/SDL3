module;

#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.Buffer;

import wd.sdl.opengl.object.Object;

export namespace wd::sdl::opengl::object
{
    struct Buffer : public Object
    {
        void BufferData(const void* data, size_t size, GLenum usage);
        void Bind();
        void Unbind();

        Buffer() = delete;
        explicit Buffer(GLenum type);
        virtual ~Buffer() override;
    };
}
