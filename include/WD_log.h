#pragma once
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>


namespace WD
{
    inline void LogError(const std::string& message, const bool _throw = false)
    {
        SDL_SetError("%s", message.c_str());
        auto error = SDL_GetError();
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", error);
        if(_throw) throw error;
    }

}
