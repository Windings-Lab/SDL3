module;

#include <memory>
#include <functional>

export module wd.sdl.opengl.Context;

export import wd.sdl.Window;
import wd.sdl.opengl.object;
import wd.sdl.Log;
import wd.utility.Constructors;

export typedef struct SDL_GLContextState* SDL_GLContext;

export namespace wd::sdl::opengl
{
    class Context : utility::NonMovable
    {
    public:
        explicit Context(const int width, const int height);

        auto GetWindow() -> Window&;
        auto GetStorage() -> const object::Storage&;

        void Iterate();

        void CreateProgram();
        void UpdateViewport(int width, int height);

        ~Context();

    private:
        Window mWindow;
        std::unique_ptr<SDL_GLContext, std::function<void(SDL_GLContext*)>> mValue;
        object::Factory mObjectFactory;
    };
}
