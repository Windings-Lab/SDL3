module;

#include <SDL_init.h>
#include <SDL_events.h>

export module wd.Engine;

export import wd.sdl;
import wd.sdl.Log;
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
        ~Engine();

    private:
        sdl::opengl::Context mGLContext;
    };
}
