export module wd.sdl.Window;

import wd.utility.Constructors;

export struct SDL_Window;

export namespace wd::sdl
{
	class Window : utility::NonMovable
	{
	public:
		Window(int width, int height);

		int Width() const noexcept;
		int Height() const noexcept;

		void Update() noexcept;

		~Window();

		SDL_Window* operator->() const noexcept;
		SDL_Window* operator*() const noexcept;

	private:
		SDL_Window* mValue = nullptr;

		int mWidth;
		int mHeight;
	};
}
