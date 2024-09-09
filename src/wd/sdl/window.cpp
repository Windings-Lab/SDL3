module;

#include <format>
#include <SDL3/SDL_video.h>

module wd.sdl.Window;

namespace wd::sdl
{
    Window::Window(const int width, const int height)
        : mWidth(width)
        , mHeight(height)
    {
        auto* window = SDL_CreateWindow("Hello SDL and OpenGL"
            , width
            , height
            , SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        if (!window)
        {
            LogError(std::format("Failed to create window!"), true);
        }

        mValue = window;
    }

    int Window::Width() const
    {
        return mWidth;
    }

    int Window::Height() const
    {
        return mHeight;
    }

    void Window::Update()
    {
        SDL_GetWindowSize(mValue, &mWidth, &mHeight);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(mValue);
    }

    SDL_Window* Window::operator->() const noexcept
    {
        return mValue;
    }

    SDL_Window* Window::operator*() const noexcept
    {
        return mValue;
    }
}
