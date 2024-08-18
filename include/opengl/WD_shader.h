#pragma once
#include "utility/WD_constructors.h"

namespace WD
{
    struct ShaderFactory;

    struct Shader : Utillity::NonCopyable
    {
        class Container
        {
        public:
            Container() = default;

            void Add(Shader& shader);
            Shader Extract(const GLchar* path);
            Shader Extract(GLuint ID);

        private:
            std::unordered_map<std::string, Shader> ByPath;
            std::unordered_map<GLuint, std::string> ByID;
        };

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;
        ~Shader();

        bool operator!() const;

        const GLuint ID;
        const char* const Path;
        const GLenum Type;

    private:
        friend ShaderFactory;
        Shader() = delete;
        Shader(const GLchar* path, GLenum type);
        void swap(Shader& other) noexcept;
    };

    struct ShaderFactory
    {
        Shader Create(const GLchar* path, GLenum type);
        bool CompileSuccess(const Shader& shader);
    };

    class ShaderProgram : Utillity::NonCopyable, Utillity::NonMovable
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void Use() noexcept;
        bool AddShader(Shader& shader);
        bool RemoveShader(const GLchar* path);
        bool RemoveShader(GLuint ID);

    private:
        bool DetachShader(const Shader& shader);

    public:
        const GLuint ID;
        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID

    private:
        Shader::Container mShaders;
    };
}
