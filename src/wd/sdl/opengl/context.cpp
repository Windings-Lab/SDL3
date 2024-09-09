module;

#include <SDL3/SDL_video.h>
#include <memory>

#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_log.h>

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.Context;

#ifndef NDEBUG
namespace
{
    void GLAD_API_PTR opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user)
    {
        if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
        SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "OpenGL error Message: %s", message);
    }
}
#endif

namespace wd::sdl::opengl
{
    Context::Context(const int width, const int height)
        : mWindow(width, height)
          , mValue(nullptr, [](const SDL_GLContext* context)
          {
              SDL_GL_DestroyContext(*context);
          })
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

        SDL_GLContext context = SDL_GL_CreateContext(*mWindow);
        SDL_assert(context);

        mValue.reset(&context);

        SDL_assert(gladLoadGL(SDL_GL_GetProcAddress));

        UpdateViewport(mWindow.Width(), mWindow.Height());
#ifndef NDEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_debug_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    }

    auto Context::GetWindow() -> Window&
    {
        return mWindow;
    }

    auto Context::GetObjectFactory() -> object::Factory&
    {
        return mObjectFactory;
    }

    auto Context::GetStorage() const -> const object::Storage&
    {
        return mObjectFactory.GetStorage();
    }

    void Context::Iterate()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Engine->Shader[0]->Use();
        //glBindVertexArray(Engine->Shader[0]->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glBindVertexArray(0);
    }

    void Context::UpdateViewport(const int width, const int height)
    {
        glViewport(0, 0, width, height);
    }

    SDL_GLContext Context::operator->() const noexcept
    {
        return *mValue.get();
    }

    SDL_GLContext Context::operator*() const noexcept
    {
        return *mValue.get();
    }
}
