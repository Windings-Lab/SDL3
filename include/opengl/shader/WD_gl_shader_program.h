#pragma once

#include "opengl/shader/WD_gl_shader_container.h"

import wd.utility.Constructors;

namespace WD::GL
{
    class Shader;
}

namespace WD::GL
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
        boost::multi_index::shader_container_ptr mShaders;
    };
}
