module;

#ifndef NDEBUG
#include <cassert>
#include <thread>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#endif

module wd.sdl.Log;

namespace wd::sdl
{
    void Assert(const std::string& message)
    {
#ifndef NDEBUG
        SDL_SetError("%s", message.c_str());
        auto error = SDL_GetError();
        const auto msg = std::format("Thread {0}: {1}", std::this_thread::get_id(), error);
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", msg.c_str());
        assert(false);
#endif
    }
}
