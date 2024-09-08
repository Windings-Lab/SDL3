module;

#include <stdexcept>
#include <thread>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>

module wd.sdl.Log;

namespace wd::sdl
{
    void LogError(const std::string& message, const bool _throw)
    {
        SDL_SetError("%s", message.c_str());
        auto error = SDL_GetError();
        auto msg = std::format("Thread {0}: {1}", std::this_thread::get_id(), error);
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", msg.c_str());
        if(_throw) throw std::runtime_error(error);
    }
}
