#pragma once

struct SDL_Window;

namespace WD
{
    namespace GL
    {
        class Context;
    }

    class Window
    {
    public:
        Window(int width, int height);

        SDL_Window* Get() const;

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
