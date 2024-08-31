#include "opengl/WD_gl_shader.h"

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_filesystem.h>

namespace WD::GL
{
    auto ShaderFactory::Create(const GLchar* path, const GLenum type) -> Shader
    {
        if(SDL_GetPathInfo(path, nullptr) == -1)
        {
            LogError(SDL_GetError(), true);
        }

        Shader shader(path, type);
        const char* code = static_cast<const char*>(SDL_LoadFile(path, nullptr));
        glShaderSource(shader.ID, 1, &code, nullptr);
        glCompileShader(shader.ID);

        if(!CompileSuccess(shader))
        {
            throw std::runtime_error("Failed to compile shader");
        }

        return shader;
    }

    auto ShaderFactory::CompileSuccess(const Shader& shader) -> bool
    {
        // Check for successful compilation
        int success;
        glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            constexpr int bufSize = 512;
            char infolog[bufSize];
            glGetShaderInfoLog(shader.ID, bufSize, nullptr, infolog);
            LogError(std::format("Shader compilation failed:\n"
                         "Info: %s\n", infolog,
                         "Path: %s\n", shader.Path,
                         "Type: %s", shader.Type));
        }

        return success;
    }
}
