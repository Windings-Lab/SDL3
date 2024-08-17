#pragma once

namespace WD
{
    struct ShaderFactory;

    struct Shader
    {
        Shader(const GLchar* path, GLenum type);
        ~Shader();

        bool operator!() const;

        const GLuint ID;
        const char* const Path;
        const GLenum Type;
    };

    struct ShaderFactory
    {
        std::unique_ptr<Shader> Create(const GLchar* path, GLenum type);
        bool CompileSuccess(const Shader& shader);
    };

    class ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void Use() noexcept;
        bool AddShader(std::unique_ptr<Shader> shader);
        bool RemoveShader(const GLchar* path);
        bool RemoveShader(const GLuint ID);

        const GLuint ID;
        GLuint VAO; // Vertex Array Object ID
        GLuint EBO; // Element Buffer Object ID

    private:
        bool DetachShader(const Shader& shader);
        std::unordered_map<std::string, std::unique_ptr<Shader>> mShadersByPath;
        std::unordered_map<GLuint, std::string> mShadersByID;
    };

    inline std::unique_ptr<ShaderProgram> CreateShaderProgram()
    {
        ShaderFactory shaderFactory;
        std::unique_ptr<Shader> vertShader = shaderFactory.Create("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        std::unique_ptr<Shader> fragShader = shaderFactory.Create("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);

        std::unique_ptr<ShaderProgram> shaderProgram = std::make_unique<ShaderProgram>();
        shaderProgram->AddShader(std::move(vertShader));
        shaderProgram->AddShader(std::move(fragShader));

        // ====== Creating Vertex Array Object ======
        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        shaderProgram->VAO = VAO;
        glBindVertexArray(VAO);
        // ====== Creating Vertex Array Object ======

        // ====== Creating and buffering Vertex Buffer Object ======
        GLuint VBO = 0;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        constexpr float vertices[] =
        {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
        };
        glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // ====== Creating and buffering Vertex Buffer Object ======

        // ====== Creating and buffering Element Buffer Object ======
        GLuint EBO = 0;
        glGenBuffers(1, &EBO);
        shaderProgram->EBO = EBO;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        const unsigned int vertexIndices[] =
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        glNamedBufferData(EBO, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
        // ====== Creating and buffering Element Buffer Object ======

        // Teaching OpenGL about vertex attributes
        // 1-4: axes count
        // Binds current bounded to GL_ARRAY_BUFFER VBO
        constexpr int axes = 3;
        glVertexAttribPointer(0, axes, GL_FLOAT, GL_FALSE, axes * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Unbinding VBO after using glVertexAttribPointer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return shaderProgram;
    }
}
