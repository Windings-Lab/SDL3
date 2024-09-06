module;

#include "opengl/gl.h"

export module wd.gl.object.Buffer;

import wd.gl.object.Object;

export namespace wd::gl
{
    struct Buffer : public Object
    {
        void BufferData(const void* data, size_t size, GLenum usage);
        void Unbind();

        Buffer() = delete;
        explicit Buffer(GLenum type);
        virtual ~Buffer() override;
    };
}
