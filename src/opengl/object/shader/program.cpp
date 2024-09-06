module;

#include <format>
#include "opengl/gl.h"

module wd.gl.object.shader.Program;

import wd.engine.Log;

namespace wd::gl
{
    Program::Program()
        : Object(glCreateProgram(), GL_PROGRAM)
    {
    }

    Program::~Program()
    {
        if(ID == 0) return;

        glDeleteProgram(ID);

        const auto error = glGetError();
        if(error != GL_NO_ERROR)
            LogError(std::format("Program was not deleted"));
    }

    void Program::Use() const noexcept
    {
        glUseProgram(ID);
    }

    void Program::Attach(const Shader* shader)
    {
        glAttachShader(ID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Failed to attach shader"), true);
        }

        glLinkProgram(ID);

        mShaders.insert(shader);
    }

    auto Program::DetachBy(const GLuint id) -> const Shader*
    {
        auto& index = mShaders.get<0>();
        const auto shader = index.extract(id).value();
        Detach(*shader);

        return shader;
    }

    auto Program::DetachBy(const GLchar* path) -> const Shader*
    {
        auto& index = mShaders.get<1>();
        const auto shader = index.extract(path).value();
        Detach(*shader);

        return shader;
    }

    void Program::Detach(const Shader& shader)
    {
        glDetachShader(ID, shader.ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Failed to detach shader"), true);
        }
    }
}
