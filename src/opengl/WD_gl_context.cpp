#include "opengl/WD_gl_context.h"
#include "opengl/buffers/WD_gl_buffer.h"
#include "opengl/WD_gl_shader.h"

#include "engine/WD_window.h"

#include "SDL3/SDL_video.h"

#ifndef NDEBUG
namespace
{
    void GLAD_API_PTR opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user)
    {
        if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
        WD::LogError(std::format("OpenGL DEBUG Message: {0}", message));
    }
}
#endif

namespace WD::GL
{
    Context::Context(Window& window)
        : mWindow(window)
    {
        // OpenGL Version 4.6
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

        // All core and deprecated OPENGL function are available
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        // Double buffer for window swap
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#ifndef NDEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

        const SDL_GLContext context = SDL_GL_CreateContext(mWindow.Get());
        if (!context)
        {
            LogError(std::format("OpenGL Context failed to create!"), true);
        }
        mValue = context;

        if(!gladLoadGL(SDL_GL_GetProcAddress))
        {
            LogError(std::format("GLAD failed to initialize"), true);
        }

        UpdateViewport(mWindow.Width(), mWindow.Height());
#ifndef NDEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_debug_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    }

    void Context::Iterate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Engine->Shader[0]->Use();
        //glBindVertexArray(Engine->Shader[0]->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        SDL_GL_SwapWindow(mWindow.Get());
    }

    void Context::CreateShaderProgram()
    {
        ShaderFactory shaderFactory;
        auto&& vertShader = shaderFactory.Create("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        auto&& fragShader = shaderFactory.Create("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);

        auto shaderProgram = std::make_unique<ShaderProgram>();
        shaderProgram->Attach(std::move(vertShader));
        shaderProgram->Attach(std::move(fragShader));

        // ====== Creating Vertex Array Object ======
        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        shaderProgram->VAO = VAO;
        glBindVertexArray(VAO);
        // ====== Creating Vertex Array Object ======

        // ====== Creating and buffering Vertex Buffer Object ======
        Buffer VBO;
        VBO.BindTo(GL_ARRAY_BUFFER);
        constexpr float vertices[] =
        {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
        };
        VBO.BufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
        mBuffers.emplace_back(std::move(VBO));
        // ====== Creating and buffering Vertex Buffer Object ======

        // ====== Creating and buffering Element Buffer Object ======
        Buffer EBO;
        EBO.BindTo(GL_ELEMENT_ARRAY_BUFFER);
        const unsigned int vertexIndices[] =
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        EBO.BufferData(vertexIndices, sizeof(vertexIndices), GL_STATIC_DRAW);
        shaderProgram->EBO = EBO.ID();
        mBuffers.emplace_back(std::move(EBO));
        // ====== Creating and buffering Element Buffer Object ======

        // Teaching OpenGL about vertex attributes
        // 1-4: axes count
        // Binds current bounded to GL_ARRAY_BUFFER VBO
        constexpr auto axes = 3;
        glVertexAttribPointer(0, axes, GL_FLOAT, GL_FALSE, axes * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Unbinding VBO after using glVertexAttribPointer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        shaderProgram->Use();
        ShaderPrograms.emplace_back(std::move(shaderProgram));
    }

    void Context::UpdateViewport(const int width, const int height)
    {
        glViewport(0, 0, width, height);
    }

    Context::~Context()
    {
        ShaderPrograms.clear();
        mBuffers.clear();
        SDL_GL_DestroyContext(mValue);
    }
}
