module;

#include <SDL3/SDL_video.h>

#include <SDL3/SDL_assert.h>

module wd.sdl.Window;

namespace wd::sdl
{
	Window::Window(const int width, const int height)
		: mWidth(width)
		, mHeight(height)
	{
		auto* window = SDL_CreateWindow(
				"Hello SDL and OpenGL"
				, width
				, height
				, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		SDL_assert(window);

		mValue = window;
	}

	int Window::Width() const noexcept
	{
		return mWidth;
	}

	int Window::Height() const noexcept
	{
		return mHeight;
	}

	void Window::Update() noexcept
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
