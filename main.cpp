#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"
#include "SDL3/SDL.h"

#include "engine/WD_engine.h"
#include "engine/WD_log.h"
#include "engine/keyboard/WD_keyboard.h"

#include "opengl/WD_shader.h"
#include "opengl/buffers/WD_gl_buffer.h"

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

namespace WD
{
    void CreateShaderProgram(Engine* engine)
    {
        ShaderFactory shaderFactory;
        Shader vertShader = shaderFactory.Create("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        Shader fragShader = shaderFactory.Create("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);

        std::unique_ptr<ShaderProgram> shaderProgram = std::make_unique<ShaderProgram>();
        shaderProgram->AddShader(vertShader);
        shaderProgram->AddShader(fragShader);

        // ====== Creating Vertex Array Object ======
        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        shaderProgram->VAO = VAO;
        glBindVertexArray(VAO);
        // ====== Creating Vertex Array Object ======

        // ====== Creating and buffering Vertex Buffer Object ======
        GL::Buffer VBO;
        VBO.BindTo(GL_ARRAY_BUFFER);
        constexpr float vertices[] =
        {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
        };
        VBO.BufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
        engine->Buffers.emplace_back(std::move(VBO));
        // ====== Creating and buffering Vertex Buffer Object ======

        // ====== Creating and buffering Element Buffer Object ======
        GL::Buffer EBO;
        EBO.BindTo(GL_ELEMENT_ARRAY_BUFFER);
        const unsigned int vertexIndices[] =
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        EBO.BufferData(vertexIndices, sizeof(vertexIndices), GL_STATIC_DRAW);
        shaderProgram->EBO = EBO.ID();
        engine->Buffers.emplace_back(std::move(EBO));
        // ====== Creating and buffering Element Buffer Object ======

        // Teaching OpenGL about vertex attributes
        // 1-4: axes count
        // Binds current bounded to GL_ARRAY_BUFFER VBO
        constexpr int axes = 3;
        glVertexAttribPointer(0, axes, GL_FLOAT, GL_FALSE, axes * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Unbinding VBO after using glVertexAttribPointer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        shaderProgram->Use();
        engine->ShaderPrograms.emplace_back(std::move(shaderProgram));
    }
}

int SDL_AppInit(void **appstate, int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_SetError("SDL failed to initialize!");
        SDL_LogError(0, "%s", SDL_GetError());

        return SDL_APP_FAILURE;
    }

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

    constexpr int Width = 800;
    constexpr int Height = 600;
    auto* Window = SDL_CreateWindow("Hello SDL and OpenGL", Width, Height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if (!Window)
    {
        SDL_SetError("SDL failed to initialize!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    auto* Context = SDL_GL_CreateContext(Window);
    if (!Context)
    {
        SDL_DestroyWindow(Window);
        SDL_SetError("OpenGL Context failed to create!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    // GLAD initialization
    if(!gladLoadGL(SDL_GL_GetProcAddress))
    {
        SDL_DestroyWindow(Window);
        SDL_SetError("GLAD failed to initialize!");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    // OpenGL Viewport dimensions
    glViewport(0, 0, Width, Height);
#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_debug_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

    // Creating an instance for an SDL appstate
    WD::Engine* Engine = new WD::Engine(Window, Context);
    *appstate = static_cast<void*>(Engine);

    CreateShaderProgram(Engine);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5.f);

    Engine->ShaderPrograms[0]->Use();

    return SDL_APP_CONTINUE;
}

int SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    const auto* Engine = static_cast<WD::Engine*>(appstate);

    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        {
            return WD::Keyboard::Handle_Input(event->key.key);
        }
    case SDL_EVENT_QUIT:
        {
            SDL_Log("Quiting!");
            return SDL_APP_SUCCESS;
        }
    case SDL_EVENT_WINDOW_RESIZED:
        {
            int Width = 0;
            int Height = 0;
            SDL_GetWindowSize(Engine->GetWindow(), &Width, &Height);
            glViewport(0, 0, Width, Height);

            SDL_Log("Window resized: %dx%d", Width, Height);
            break;
        }
    default:
        {
            break;
        }
    }

    return SDL_APP_CONTINUE;
}

int SDL_AppIterate(void *appstate)
{
    const WD::Engine* Engine = static_cast<WD::Engine*>(appstate);

    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Engine->Shader[0]->Use();
    //glBindVertexArray(Engine->Shader[0]->VAO);
    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);

    SDL_GL_SwapWindow(Engine->GetWindow());
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
    delete static_cast<WD::Engine*>(appstate);
}
