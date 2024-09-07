module;

#include <format>
#include <bits/ranges_algo.h>

#include "opengl/gl.h"

module wd.gl.object.shader.Program;

import wd.engine.Log;
import wd.gl.object.shader.Shader;

namespace wd::gl::object::shader
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

    void Program::Attach(Shader* shader)
    {
        glAttachShader(ID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Failed to attach shader"), true);
        }

        glLinkProgram(ID);

        mShaders.emplace_back(shader);
    }

    auto Program::DetachBy(GLuint id) -> Shader*
    {
        const auto [first, last] = std::ranges::remove_if(mShaders, [id](Shader* shader)
        {
            return shader->ID == id;
        });
        const auto shader = *mShaders.erase(first, last).base();
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
