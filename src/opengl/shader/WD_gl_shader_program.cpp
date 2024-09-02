#include "opengl/shader/WD_gl_shader_program.h"

#include "opengl/shader/WD_gl_shader.h"

namespace WD::GL
{
    ShaderProgram::ShaderProgram()
        : VAO(0)
        , EBO(0)
        , mID(glCreateProgram())
    {
        if (mID == 0) throw glGetError();
    }

    ShaderProgram::~ShaderProgram()
    {
        if(mID == 0) return;

        glDeleteProgram(mID);

        const auto error = glGetError();
        if(error != GL_NO_ERROR)
            LogError(std::format("Program was not deleted"));
    }

    void ShaderProgram::Use() const noexcept
    {
        glUseProgram(mID);
    }

    void ShaderProgram::Attach(const Shader* shader)
    {
        glAttachShader(mID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            throw std::runtime_error("Failed to attach shader");
        }

        glLinkProgram(mID);

        mShaders.insert(shader);
    }

    auto ShaderProgram::DetachBy(const GLuint id) -> const Shader*
    {
        auto& index = mShaders.get<0>();
        const auto shader = index.extract(id).value();
        Detach(*shader);

        return shader;
    }

    auto ShaderProgram::DetachBy(const GLchar* path) -> const Shader*
    {
        auto& index = mShaders.get<1>();
        const auto shader = index.extract(path).value();
        Detach(*shader);

        return shader;
    }

    void ShaderProgram::Detach(const Shader& shader)
    {
        glDetachShader(mID, shader.ID);
        if(glGetError() != GL_NO_ERROR)
        {
            throw std::runtime_error("Failed to detach shader");
        }
    }
}
