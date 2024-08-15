#pragma once
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_iostream.h"

#include "glad/gl.h"

namespace WD
{
    struct Shader
    {
        GLuint ID;
        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID
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

    static bool GL_CreateCompileShader(GLuint& ID, const GLenum type, const GLchar* shaderPath)
    {
        if(SDL_GetPathInfo(shaderPath, nullptr) == -1)
        {
            SDL_LogError(0, "%s", SDL_GetError());
            return false;
        }

        const void* codeptr = SDL_LoadFile(shaderPath, nullptr);
        const char* code = static_cast<const char*>(codeptr);
        ID = glCreateShader(type);
        glShaderSource(ID, 1, &code, nullptr);
        glCompileShader(ID);
        return GL_ShaderCompileSuccess(ID);
    }

    static Shader CreateShaderProgram()
    {
        // Vertex Shader Creation
        GLuint vertexShader = 0;
        GL_CreateCompileShader(vertexShader, GL_VERTEX_SHADER, "assets/shaders/vertex.vert");
    
        // Fragment Shader Creation
        GLuint fragmentShader = 0;
        GL_CreateCompileShader(fragmentShader, GL_FRAGMENT_SHADER, "assets/shaders/fragment.frag");

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
