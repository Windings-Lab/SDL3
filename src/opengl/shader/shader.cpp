module;

#include <format>
#include <SDL_filesystem.h>
#include <SDL_iostream.h>

#include "opengl/glad/gl.h"

module wd.gl.shader.Shader;

import wd.engine.Log;

namespace
{
    auto CompileSuccess(const wd::gl::Shader& shader) -> bool
    {
        // Check for successful compilation
        int success;
        glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            constexpr int bufSize = 512;
            char infolog[bufSize];
            glGetShaderInfoLog(shader.ID, bufSize, nullptr, infolog);
            wd::LogError(std::format("Shader compilation failed:\n"
                                     "Info: %s\n", infolog,
                                     "Path: %s\n", shader.Path,
                                     "Type: %s", shader.Type));
        }

        return success;
    }
}

namespace wd::gl
{
    Shader::Shader(const GLchar* path, const GLenum type)
        : ID(glCreateShader(type)), Path(path), Type(type)
    {
        const auto error = glGetError();
        if(error || ID == 0)
        {
            LogError(std::format("Shader is not created: %s", path), true);
        }
    }

    void Shader::Compile() const
    {
        if(SDL_GetPathInfo(Path, nullptr) == -1)
        {
            LogError(SDL_GetError(), true);
        }

        const char* code = static_cast<const char*>(SDL_LoadFile(Path, nullptr));
        glShaderSource(ID, 1, &code, nullptr);
        glCompileShader(ID);

        if(!CompileSuccess(*this))
        {
            LogError(std::format("Failed to compile shader"), true);
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(ID);
    }
}
