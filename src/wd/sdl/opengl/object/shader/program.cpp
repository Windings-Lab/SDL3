module;

#include <format>
#if defined(__clang__)
#include <bits/ranges_algo.h>
#elif defined(_MSC_VER)
#include <algorithm>
#endif

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.shader.Program;

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
            Assert(std::format("Program was not deleted"));
    }

    void Program::Use() const noexcept
    {
        glUseProgram(ID);
    }

    void Program::Link() const noexcept
    {
        glLinkProgram(ID);
    }

    void Program::Attach(Shader* shader)
    {
        if(!shader) return;

        glAttachShader(ID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            Assert(std::format("Failed to attach shader"));
        }

        mShaders.emplace_back(shader);
    }

    auto Program::DetachBy(GLuint id) -> Shader*
    {
        const auto pte = std::ranges::remove_if(mShaders, [id](Shader* shader)
        {
            return shader->ID == id;
        });
        if(pte.size() == 0)
        {
            Assert(std::format("Failed to find shader to detach by ID"));
        }
#if defined(__clang__)
        const auto shader = *mShaders.erase(pte.begin(), pte.end()).base();
#elif defined(_MSC_VER)
        const auto shader = *mShaders.erase(pte.begin(), pte.end());
#endif
        glDetachShader(ID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            Assert(std::format("Failed to detach shader"));
        }

        return shader;
    }
}
