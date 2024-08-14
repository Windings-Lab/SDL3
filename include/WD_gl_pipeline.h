#pragma once
#include <SDL3/SDL_log.h>

#include "glad/gl.h"

namespace WD
{
    struct Shader
    {
        GLuint ID;
        GLuint VAO; // Vertex Array Object ID
        GLuint EBO;
    };
    
    static bool GL_ShaderCompileSuccess(const GLuint& shader)
    {
        // Check for succesfull compilation
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            constexpr int bufSize = 512;
            char infolog[bufSize];
            glGetShaderInfoLog(shader, bufSize, nullptr, infolog);
            SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infolog);
        }

        return success;
    }

    static bool GL_CreateCompileShader(GLuint& ID, const GLchar* code, GLenum type)
    {
        ID = glCreateShader(type);
        glShaderSource(ID, 1, &code, nullptr);
        glCompileShader(ID);
        return GL_ShaderCompileSuccess(ID);
    }

    static Shader CreateShaderProgram()
    {
        // Vertex Shader Creation
        GLuint vertexShader = 0;
        const GLchar* vertexShaderSource =
            "#version 460 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
                "\tgl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        GL_CreateCompileShader(vertexShader, vertexShaderSource, GL_VERTEX_SHADER);
    
        // Fragment Shader Creation
        GLuint fragmentShader = 0;
        const GLchar* fragmentShaderSource =
            "#version 460 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
                "\tFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";
        GL_CreateCompileShader(fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER);

        // Creating shader program and linking shaders
        const GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // No need for shaders after linking
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        // Unsigned int. Creating OpenGL Object
        // Creating Vertex Array Object
        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // Creating Vertex Buffer Objects
        GLuint buffers[2] =
        {
            0, // VBO
            0  // EBO
        };
        glGenBuffers(2, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        
        // Vertex Input
        constexpr float vertices[] =
        {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
        };
        const unsigned int indices[] =
        { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        // Buffering verticies into GPU
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Linking vertex attributes. Teaching OpenGL about
        // 1-4: axes count, stride is number of axes times size of data type
        constexpr int axes = 3;
        glVertexAttribPointer(0, axes, GL_FLOAT, GL_FALSE, axes * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Unbinding VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return {shaderProgram, VAO, buffers[1] };
    }
}
