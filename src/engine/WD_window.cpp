#include "engine/WD_window.h"

#include "SDL3/SDL_video.h"

namespace WD
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

    SDL_Window* Window::Get() const
    {
        return mValue;
    }

    int Window::Width() const
    {
        return mWidth;
    }

    int Window::Height() const
    {
        return mHeight;
    }

    void Window::SetWidth(const int width)
    {
        mWidth = width;
    }

    void Window::SetHeight(const int height)
    {
        mHeight = height;
    }

    void Window::Update()
    {
        SDL_GetWindowSize(mValue, &mWidth, &mHeight);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(mValue);
    }
}
