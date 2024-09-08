module;

#include <SDL_video.h>
#include <format>
#include <memory>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.Context;

#ifndef NDEBUG
namespace
{
    void GLAD_API_PTR opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user)
    {
        if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
        wd::sdl::LogError(std::format("OpenGL error Message: {0}", message));
    }
}
#endif

namespace wd::sdl::opengl
{
    Context::Context(const int width, const int height)
        : mWindow(width, height)
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
            sdl::LogError(std::format("OpenGL Context failed to create!"), true);
        }
        mValue = context;

        if(!gladLoadGL(SDL_GL_GetProcAddress))
        {
            sdl::LogError(std::format("GLAD failed to initialize"), true);
        }

        UpdateViewport(mWindow.Width(), mWindow.Height());
#ifndef NDEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_debug_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    }

    auto Context::GetWindow() -> sdl::Window&
    {
        return mWindow;
    }

    void Context::Iterate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Engine->Shader[0]->Use();
        //glBindVertexArray(Engine->Shader[0]->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glBindVertexArray(0);

        SDL_GL_SwapWindow(mWindow.Get());
    }

    auto Context::CreateShader(const GLchar* path, const GLenum type) -> object::Shader*
    {
        auto shader = std::make_unique<object::Shader>(path, type);
        shader->Compile();
        const auto shaderPtr = shader.get();

        mShaders.emplace_back(std::move(shader));

        return shaderPtr;
    }

    void Context::CreateProgram()
    {
        const auto program = Programs.emplace_back(std::make_unique<object::shader::Program>()).get();
        auto vertShader = CreateShader("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        auto fragShader = CreateShader("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);

        program->Attach(vertShader);
        program->Attach(fragShader);

        //GL_ARRAY_BUFFER
        //GL_ELEMENT_ARRAY_BUFFER

        // Creating Vertex Array Object
        auto VBO = std::make_unique<object::Buffer>(GL_ARRAY_BUFFER);
        auto EBO = std::make_unique<object::Buffer>(GL_ELEMENT_ARRAY_BUFFER);
        auto VAO = std::make_unique<object::vertex::Array>(*VBO, *EBO);

        // ====== Buffering Vertex Buffer Object ======
        constexpr GLdouble vertices[] =
        {
            0.5, 0.5, 0.0, // top right
            0.5, -0.5, 0.0, // bottom right
            -0.5, -0.5, 0.0, // bottom left
            -0.5, 0.5, 0.0 // top left
        };
        VAO->VBO.Bind();
        VAO->VBO.BufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
        // ====== Buffering Vertex Buffer Object ======

        // ====== Buffering Element Buffer Object ======
        constexpr GLuint vertexIndices[] =
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        VAO->EBO.Bind();
        VAO->EBO.BufferData(vertexIndices, sizeof(vertexIndices), GL_STATIC_DRAW);
        // ====== Buffering Element Buffer Object ======

        VAO->ReadVBO();
        VAO->Enable();

        // After using glVertexAttribPointer
        VAO->VBO.Unbind();

        program->Use();
        
        mVertexArrays.emplace_back(std::move(VAO));
        mBuffers.emplace_back(std::move(VBO));
        mBuffers.emplace_back(std::move(EBO));
    }

    void Context::UpdateViewport(const int width, const int height)
    {
        glViewport(0, 0, width, height);
    }

    Context::~Context()
    {
        Programs.clear();
        mShaders.clear();
        mBuffers.clear();
        mVertexArrays.clear();
        SDL_GL_DestroyContext(mValue);
    }
}
