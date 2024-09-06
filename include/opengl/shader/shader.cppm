module;

#include "opengl/glad/gl.h"

export module wd.gl.shader.Shader;

import wd.utility.Constructors;

export namespace wd::gl
{
    class Shader : utility::NonMovable
    {
    public:
        Shader(const GLchar* path, GLenum type);

        void Compile() const;

        const GLuint ID;
        const GLchar* const Path;
        const GLenum Type;

    public:
        ~Shader();

    private:

        Shader() = delete;
    };
}
