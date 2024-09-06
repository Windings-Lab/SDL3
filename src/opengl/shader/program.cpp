module;

#include <format>
#include "opengl/glad/gl.h"

module wd.gl.shader.Program;

import wd.engine.Log;
import wd.gl.shader.Shader;

namespace wd::gl
{
    ShaderProgram::ShaderProgram()
        : VAO(0)
        , EBO(0)
        , mID(glCreateProgram())
    {
        const auto error = glGetError();
        if (error || mID == 0)
        {
            LogError(std::format("Program failed to create", error), true);
        }
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
            LogError(std::format("Failed to attach shader"), true);
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
            LogError(std::format("Failed to detach shader"), true);
        }
    }
}
