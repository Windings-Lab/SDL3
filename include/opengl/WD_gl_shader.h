#pragma once
#include "utility/WD_constructors.h"

namespace WD::GL
{
    class Shader : Utillity::NonCopyable
    {
    public:
        friend struct ShaderFactory;
        GLuint GetID() const;

    private:
        GLuint ID;
        const char* Path;
        GLenum Type;

    public:
        Shader(Shader&& other) noexcept;
        auto operator=(Shader&& other) noexcept -> Shader&;
        ~Shader();
        auto operator!() const -> bool;
        class Container
        {
        public:
            Container() = default;

            auto Add(Shader& shader) -> void;
            auto Extract(const GLchar* path) -> Shader;
            auto Extract(GLuint ID) -> Shader;

        private:
            std::unordered_map<std::string, Shader> ByPath;
            std::unordered_map<GLuint, std::string> ByID;
        };

    private:
        Shader(const GLchar* path, GLenum type);
        Shader() = delete;
        auto swap(Shader& other) noexcept -> void;
    };

    struct ShaderFactory
    {
        auto Create(const GLchar* path, GLenum type) -> Shader;
        auto CompileSuccess(const Shader& shader) -> bool;
    };

    class ShaderProgram : Utillity::NonCopyable, Utillity::NonMovable
    {
    public:
        auto Use() noexcept -> void;
        auto Attach(Shader& shader) -> bool;
        auto Detach(const GLchar* path) -> bool;
        auto Detach(GLuint ID) -> bool;

        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID

    public:
        ShaderProgram();
        ~ShaderProgram();

    private:
        auto DetachShader(const Shader& shader) -> bool;
        GLuint ID;
        Shader::Container mShaders;
    };
}
