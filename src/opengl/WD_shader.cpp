#include "opengl/WD_shader.h"
#include "engine/WD_log.h"

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_filesystem.h>

namespace WD
{
    Shader::Shader(const GLchar* path, const GLenum type)
        : ID(glCreateShader(type)), Path(path), Type(type)
    {
        if(ID == GL_INVALID_ENUM) throw glGetError();
        if(ID == 0) LogError(std::format("Shader is not created: %s", path), true);
    }

    Shader::~Shader()
    {
        glDeleteShader(ID);
    }

    bool Shader::operator!() const
    {
        return ID == 0;
    }

    std::unique_ptr<Shader> ShaderFactory::Create(const GLchar* path, GLenum type)
    {
        if(SDL_GetPathInfo(path, nullptr) == -1)
        {
            LogError(SDL_GetError());
            return nullptr;
        }

        auto shader = std::make_unique<Shader>(path, type);
        const char* code = static_cast<const char*>(SDL_LoadFile(path, nullptr));
        glShaderSource(shader->ID, 1, &code, nullptr);
        glCompileShader(shader->ID);

        if(!CompileSuccess(*shader))
        {
            return nullptr;
        }

        return shader;
    }

    bool ShaderFactory::CompileSuccess(const Shader& shader)
    {
        // Check for succesfull compilation
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

    ShaderProgram::ShaderProgram()
        : ID(glCreateProgram())
        , VAO(0)
        , EBO(0)
    {
        if (ID == 0) throw glGetError();
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(ID);

        auto error = glGetError();
        if(error != GL_NO_ERROR)
            LogError(std::format("Program was not deleted"));
    }

    void ShaderProgram::Use() noexcept
    {
        glUseProgram(ID);
    }

    bool ShaderProgram::AddShader(std::unique_ptr<Shader> shader)
    {
        glAttachShader(ID, shader->ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Shader attach failed"));
            return false;
        }

        if(!mShadersByID.emplace(shader->ID, shader->Path).second)
        {
            DetachShader(*shader);
            return false;
        }
        if(!mShadersByPath.emplace(shader->Path, std::move(shader)).second)
        {
            mShadersByID.erase(shader->ID);
            DetachShader(*shader);
            return false;
        }

        glLinkProgram(ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Program was not linked"));
            return false;
        }

        return true;
    }

    bool ShaderProgram::RemoveShader(const GLchar* path)
    {
        const auto it = mShadersByPath.find(path);
        if(it == mShadersByPath.end())
        {
            LogError(std::format("No shader with specified path: %s", path));
            return false;
        }
        const std::unique_ptr<Shader> shader = std::move(mShadersByPath.extract(path).mapped());
        DetachShader(*shader);

        return true;
    }

    bool ShaderProgram::RemoveShader(const GLuint ID)
    {
        auto it_string = mShadersByID.find(ID);
        if(it_string == mShadersByID.end())
        {
            LogError(std::format("No shader with specified ID: %i", ID));
            return false;
        }
        auto it = mShadersByPath.find(it_string->second);
        if(it == mShadersByPath.end())
        {
            LogError("No shader in ShadersByPath when it's available in ShadersByID", true);
        }
        const std::unique_ptr<Shader> shader = std::move(mShadersByPath.extract(it_string->second).mapped());
        DetachShader(*shader);

        return true;
    }

    bool ShaderProgram::DetachShader(const Shader& shader)
    {
        glDetachShader(ID, shader.ID);
        if(glGetError() != GL_NO_ERROR) LogError("Existing shader detachment failed", true);

        return true;
    }
}
