module;

#include "opengl/gl.h"

export module wd.gl.object.shader.Shader;

import wd.gl.object.Object;

export namespace wd::gl
{
    struct Shader : public Object
    {
        const GLchar* const Path;

        void Compile();

        Shader() = delete;
        Shader(const GLchar* path, GLenum type);
        virtual ~Shader() override;
    };
}
