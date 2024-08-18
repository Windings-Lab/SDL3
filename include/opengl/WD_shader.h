#pragma once
#include "utility/WD_constructors.h"

namespace WD
{
    struct ShaderFactory;

    class Shader : Utillity::NonCopyable
    {
    public:
        friend ShaderFactory;
        GLuint GetID() const;

    private:
        GLuint ID;
        const char* Path;
        GLenum Type;

    public:
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;
        ~Shader();
        bool operator!() const;
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

    private:
        Shader(const GLchar* path, GLenum type);
        Shader() = delete;
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
        void Use() noexcept;
        bool AddShader(Shader& shader);
        bool RemoveShader(const GLchar* path);
        bool RemoveShader(GLuint ID);

        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID

    public:
        ShaderProgram();
        ~ShaderProgram();

    private:
        bool DetachShader(const Shader& shader);
        GLuint ID;
        Shader::Container mShaders;
    };
}
