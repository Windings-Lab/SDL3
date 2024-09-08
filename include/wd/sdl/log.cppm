module;

#include <string>

export module wd.sdl.Log;

export namespace wd::sdl
{
    void LogError(const std::string& message, bool _throw = false);
}
