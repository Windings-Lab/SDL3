export module wd.sdl.Window;

import wd.utility.Constructors;

export struct SDL_Window;

export namespace wd::sdl
{
    class Window : utility::NonMovable
    {
    public:
        Window(int width, int height);

        auto Get() const -> SDL_Window*;

        int Width() const;
        int Height() const;

        void SetWidth(int width);
        void SetHeight(int height);

        void Update();

        ~Window();

    private:
        SDL_Window* mValue = nullptr;

        int mWidth;
        int mHeight;
    };
}
