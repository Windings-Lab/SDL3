#include "opengl/WD_gl_shader.h"

namespace WD::GL
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
        other.ID = 0;
        other.Path = nullptr;
        other.Type = 0;
    }

    Shader::~Shader()
    {
        if(!*this) return;

        glDeleteShader(ID);
    }

    auto Shader::operator=(Shader&& other) noexcept -> Shader&
    {
        if(this != &other)
        {
            Shader tmp(std::move(other));
            swap(tmp);
        }

        return *this;
    }

    auto Shader::swap(Shader& other) noexcept -> void
    {
        using std::swap;

        swap(ID, other.ID);
        swap(Path, other.Path);
        swap(Type, other.Type);
    }

    auto Shader::Container::Add(Shader& shader) -> void
    {
        ByID[shader.ID] = shader.Path;
        ByPath.emplace(shader.Path, std::move(shader));
    }

    auto Shader::Container::Extract(const GLchar* path) -> Shader
    {
        const auto it = ByPath.find(path);
        if(it == ByPath.end())
        {
            LogError(std::format("No shader with specified path: %s", path), true);
        }

        return std::move(ByPath.extract(it).mapped());
    }

    auto Shader::Container::Extract(GLuint ID) -> Shader
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

    auto Shader::GetID() const -> GLuint
    {
        return ID;
    }

    auto Shader::operator!() const -> bool
    {
        return ID == 0;
    }
}
