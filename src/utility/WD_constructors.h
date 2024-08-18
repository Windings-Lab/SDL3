#pragma once

namespace WD::Utillity
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        ~NonCopyable() = default;

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    class NonMovable
    {
    public:
        NonMovable() = default;
        ~NonMovable() = default;

        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;
    };
}
