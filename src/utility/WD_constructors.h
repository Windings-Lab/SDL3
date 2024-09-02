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
        NonCopyable(NonCopyable&&) = default;
        NonCopyable& operator=(NonCopyable&&) = default;
    };

    class NonMovable : public NonCopyable
    {
    public:
        NonMovable() = default;
        ~NonMovable() = default;

        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;
    };
}
