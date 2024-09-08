module;

#include <format>
#include <SDL_filesystem.h>
#include <SDL_iostream.h>

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.shader.Shader;

import wd.sdl.Log;

namespace
{
    auto CompileSuccess(const wd::sdl::opengl::object::Shader& shader) -> bool
    {
        // Check for successful compilation
        int success;
        glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            constexpr int bufSize = 512;
            char infolog[bufSize];
            glGetShaderInfoLog(shader.ID, bufSize, nullptr, infolog);
            wd::sdl::LogError(std::format("Shader compilation failed:\n"
                                     "Info: %s\n", infolog,
                                     "Path: %s\n", shader.Path,
                                     "Type: %s", shader.Type()));
        }

        return success;
    }
}

namespace wd::sdl::opengl::object
{
    Shader::Shader(const GLchar* path, const GLenum type)
        : Object(glCreateShader(type), type)
        , Path(path)
    {
    }

    void Shader::Compile()
    {
        if(SDL_GetPathInfo(Path, nullptr) == -1)
        {
            sdl::LogError(SDL_GetError(), true);
        }

        const char* code = static_cast<const char*>(SDL_LoadFile(Path, nullptr));
        glShaderSource(ID, 1, &code, nullptr);
        glCompileShader(ID);

        if(!CompileSuccess(*this))
        {
            sdl::LogError(std::format("Failed to compile shader"), true);
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(ID);
    }
}
