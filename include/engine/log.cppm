module;

#include <string>

export module wd.engine.Log;

export namespace WD
{
    void LogError(const std::string& message, bool _throw = false);
}
