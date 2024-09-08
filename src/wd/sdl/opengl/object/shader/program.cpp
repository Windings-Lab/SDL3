module;

#include <format>
#if defined(__clang__)
#include <bits/ranges_algo.h>
#elif defined(_MSC_VER)
#include <algorithm>
#endif

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.shader.Program;

import wd.sdl.Log;
import wd.sdl.opengl.object.shader.Shader;

namespace wd::sdl::opengl::object::shader
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
            sdl::LogError(std::format("Program was not deleted"));
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
            sdl::LogError(std::format("Failed to attach shader"), true);
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
#if defined(__clang__)
        const auto shader = *mShaders.erase(first, last).base();
#elif defined(_MSC_VER)
        const auto shader = *mShaders.erase(first, last);
#endif
        Detach(*shader);

        return shader;
    }

    void Program::Detach(const Shader& shader)
    {
        glDetachShader(ID, shader.ID);
        if(glGetError() != GL_NO_ERROR)
        {
            sdl::LogError(std::format("Failed to detach shader"), true);
        }
    }
}
