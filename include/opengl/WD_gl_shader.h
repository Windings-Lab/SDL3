#pragma once
#include "utility/WD_constructors.h"

namespace WD::GL
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
        bool Attach(Shader& shader);
        bool Detach(const GLchar* path);
        bool Detach(GLuint ID);

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
