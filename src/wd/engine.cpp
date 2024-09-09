module;

#include <SDL_init.h>
#include <format>
#include <SDL_log.h>

#include "wd/sdl/opengl/gl.h"

module wd.Engine;

namespace
{
    void DoSomething()
    {

    }

    void CreateShaderProgram(wd::sdl::opengl::Context& glContext)
    {
        auto& objectFactory = glContext.GetObjectFactory();
        const auto program = objectFactory.CreateProgram();
        auto vertShader = objectFactory.CreateShader("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        auto fragShader = objectFactory.CreateShader("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);

        program->Attach(vertShader);
        program->Attach(fragShader);

        //GL_ARRAY_BUFFER
        //GL_ELEMENT_ARRAY_BUFFER

        // Creating Vertex Array Object
        auto VBO = objectFactory.CreateBuffer(GL_ARRAY_BUFFER);
        auto EBO = objectFactory.CreateBuffer(GL_ELEMENT_ARRAY_BUFFER);
        auto VAO = objectFactory.CreateVertexArray(*VBO, *EBO);

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

        //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(5.f);

        program->Use();
    }
}

namespace wd
{
    Engine::Engine(const int width, const int height)
        : NonMovable()
        , mGLContext(width, height)
    {

    }

    auto Engine::OnInit() -> SDL_AppResult
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            sdl::LogError(std::format("SDL failed to initialize!"));
            return SDL_APP_FAILURE;
        }

        CreateShaderProgram(mGLContext);

        return SDL_APP_CONTINUE;
    }

    auto Engine::OnEvent(const SDL_Event* event) -> SDL_AppResult
    {
        switch (event->type)
        {
        case SDL_EVENT_KEY_DOWN:
            {
                return sdl::Handle_Input(event->key.key);
            }
        case SDL_EVENT_QUIT:
            {
                SDL_Log("Quiting!");
                return SDL_APP_SUCCESS;
            }
        case SDL_EVENT_WINDOW_RESIZED:
            {
                auto& window = GetWindow();
                window.Update();
                const auto width = window.Width();
                const auto height = window.Height();
                GetGLContext().UpdateViewport(width, height);

                SDL_Log("Window resized: %dx%d", width, height);
                break;
            }
        default:
            {
                break;
            }
        }

        return SDL_APP_CONTINUE;
    }

    auto Engine::OnIterate() -> SDL_AppResult
    {
        GetGLContext().Iterate();
        SDL_GL_SwapWindow(*GetGLContext().GetWindow());
        return SDL_APP_CONTINUE;
    }

    auto Engine::GetWindow() -> sdl::Window&
    {
        return mGLContext.GetWindow();
    }

    auto Engine::GetGLContext() -> sdl::opengl::Context&
    {
        return mGLContext;
    }

    Engine::~Engine()
    {
    }
}
