module;

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

export module wd.Engine;

export import wd.sdl;
import wd.utility.Constructors;

export namespace wd
{
    class Engine : utility::NonMovable
    {
    public:
        auto OnInit() -> SDL_AppResult;
        auto OnEvent(const SDL_Event* event) -> SDL_AppResult;
        auto OnIterate() -> SDL_AppResult;

        auto GetWindow() -> sdl::Window&;
        auto GetGLContext() -> sdl::opengl::Context&;

        Engine(const int width, const int height);
        ~Engine() = default;

    private:
        sdl::opengl::Context mGLContext;
    };
}
