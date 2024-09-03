module;

#include <stdexcept>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>

module wd.engine.Log;

namespace WD
{
    void LogError(const std::string& message, const bool _throw)
    {
        SDL_SetError("%s", message.c_str());
        const auto& error = SDL_GetError();
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", error);
        if(_throw) throw std::runtime_error(error);
    }
}
