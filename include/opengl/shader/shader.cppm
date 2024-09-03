export module wd.opengl.Shader;

import wd.utility.Constructors;

export namespace WD::GL
{
    class Shader : Utility::NonMovable
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
