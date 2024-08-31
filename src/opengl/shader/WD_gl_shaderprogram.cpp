#include "opengl/WD_gl_shader.h"

namespace WD::GL
{
    ShaderProgram::ShaderProgram()
    : ID(glCreateProgram())
    , VAO(0)
    , EBO(0)
    {
        if (ID == 0) throw glGetError();
    }

    ShaderProgram::~ShaderProgram()
    {
        if(ID == 0) return;

        glDeleteProgram(ID);

        auto error = glGetError();
        if(error != GL_NO_ERROR)
            LogError(std::format("Program was not deleted"));
    }

    auto ShaderProgram::Use() noexcept -> void
    {
        glUseProgram(ID);
    }

    auto ShaderProgram::Attach(Shader&& shader) -> bool
    {
        glAttachShader(ID, shader.GetID());
        if(glGetError() != GL_NO_ERROR) return false;

        mShaders.Add(std::move(shader));

        glLinkProgram(ID);

        return true;
    }

    bool ShaderProgram::Detach(const GLchar* path)
    {
        try
        {
            DetachShader(mShaders.Extract(path));
        }
        catch(const std::exception& e)
        {
            return false;
        }

        return true;
    }

    auto ShaderProgram::Detach(const GLuint ID) -> bool
    {
        try
        {
            DetachShader(mShaders.Extract(ID));
        }
        catch(const std::exception& e)
        {
            return false;
        }

        return true;
    }

    auto ShaderProgram::DetachShader(const Shader& shader) -> bool
    {
        glDetachShader(ID, shader.GetID());
        if(glGetError() != GL_NO_ERROR) LogError("Existing shader detachment failed", true);

        return true;
    }
}
