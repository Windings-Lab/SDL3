module;

#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include "opengl/glad/gl.h"

export module wd.opengl.shader.Program;

import wd.utility.Constructors;
import wd.opengl.shader.Container;

export namespace WD::GL
{
    class ShaderProgram : Utility::NonMovable
    {
    public:
        void Use() const noexcept;
        void Attach(const Shader* shader);
        auto DetachBy(GLuint id) -> const Shader*;
        auto DetachBy(const GLchar* path) -> const Shader*;

        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID

    public:
        ShaderProgram();
        ~ShaderProgram();

    private:
        auto Detach(const Shader& shader) -> void;
        GLuint mID;
        shader_container_ptr mShaders;
    };
}
