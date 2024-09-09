module;

#include <SDL3/SDL_assert.h>
#include <algorithm>
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

        SDL_assert(!glGetError());
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
        SDL_assert(!glGetError());

        mShaders.emplace_back(shader);
    }

    auto Program::DetachBy(GLuint id) -> Shader*
    {
        const auto pte = std::ranges::remove_if(mShaders, [id](Shader* shader)
        {
            return shader->ID == id;
        }).begin();
        SDL_assert(pte != mShaders.end());
#if defined(__clang__)
        const auto shader = *mShaders.erase(pte, mShaders.end()).base();
#elif defined(_MSC_VER)
        const auto shader = *mShaders.erase(pte, mShaders.end());
#endif
        glDetachShader(ID, shader->ID);
        SDL_assert(!glGetError());

        return shader;
    }
}
