#include "opengl/WD_shader.h"
#include "engine/WD_log.h"

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_filesystem.h>

namespace WD
{
    Shader::Shader(const GLchar* path, const GLenum type)
        : ID(glCreateShader(type)), Path(path), Type(type)
    {
        auto error = glGetError();
        if(error == GL_INVALID_ENUM) throw error;
        if(ID == 0) LogError(std::format("Shader is not created: %s", path), true);
    }

    Shader::Shader(Shader&& other) noexcept : ID(other.ID), Path(other.Path), Type(other.Type)
    {
        const_cast<GLuint&>(other.ID) = 0;
        const_cast<const char*&>(other.Path) = nullptr;
        const_cast<GLenum&>(other.Type) = 0;
    }

    Shader::~Shader()
    {
        if(!*this) return;

        glDeleteShader(ID);
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if(this != &other)
        {
            Shader tmp(std::move(other));
            swap(tmp);
        }

        return *this;
    }

    void Shader::swap(Shader& other) noexcept
    {
        using std::swap;

        swap(const_cast<GLuint&>(ID), const_cast<GLuint&>(other.ID));
        swap(const_cast<const char*&>(Path), const_cast<const char*&>(other.Path));
        swap(const_cast<GLenum&>(Type), const_cast<GLenum&>(other.Type));
    }

    void Shader::Container::Add(Shader& shader)
    {
        ByID[shader.ID] = shader.Path;
        ByPath.emplace(shader.Path, std::move(shader));
    }

    Shader Shader::Container::Extract(const GLchar* path)
    {
        const auto it = ByPath.find(path);
        if(it == ByPath.end())
        {
            LogError(std::format("No shader with specified path: %s", path), true);
        }

        return std::move(ByPath.extract(it).mapped());
    }

    Shader Shader::Container::Extract(GLuint ID)
    {
        const auto pathIt = ByID.find(ID);
        if(pathIt == ByID.end())
        {
            LogError(std::format("No shader with specified ID: %i", ID), true);
        }
        const auto shaderIt = ByPath.find(pathIt->second);
        if(shaderIt == ByPath.end())
        {
            LogError("No shader in ShadersByPath when it's available in ShadersByID", true);
        }
        return std::move(ByPath.extract(shaderIt).mapped());
    }

    bool Shader::operator!() const
    {
        return ID == 0;
    }

    Shader ShaderFactory::Create(const GLchar* path, GLenum type)
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

    bool ShaderFactory::CompileSuccess(const Shader& shader)
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

    ShaderProgram::ShaderProgram()
        : ID(glCreateProgram())
        , VAO(0)
        , EBO(0)
    {
        if (ID == 0) throw glGetError();
    }

    ShaderProgram::~ShaderProgram()
    {
        if(ID == 0) return;

        glDeleteProgram(ID);

        auto error = glGetError();
        if(error != GL_NO_ERROR)
            LogError(std::format("Program was not deleted"));
    }

    void ShaderProgram::Use() noexcept
    {
        glUseProgram(ID);
    }

    bool ShaderProgram::AddShader(Shader& shader)
    {
        glAttachShader(ID, shader.ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Shader attach failed"));
            return false;
        }

        mShaders.Add(shader);

        glLinkProgram(ID);
        if(glGetError() != GL_NO_ERROR)
        {
            LogError(std::format("Program was not linked"));
        }

        return true;
    }

    bool ShaderProgram::RemoveShader(const GLchar* path)
    {
        try
        {
            DetachShader(mShaders.Extract(path));
        }
        catch(const std::exception& e)
        {
            return false;
        }

        return true;
    }

    bool ShaderProgram::RemoveShader(const GLuint ID)
    {
        try
        {
            DetachShader(mShaders.Extract(ID));
        }
        catch(const std::exception& e)
        {
            return false;
        }

        return true;
    }

    bool ShaderProgram::DetachShader(const Shader& shader)
    {
        glDetachShader(ID, shader.ID);
        if(glGetError() != GL_NO_ERROR) LogError("Existing shader detachment failed", true);

        return true;
    }
}
