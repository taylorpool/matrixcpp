#pragma once

namespace math
{
    constexpr int product()
    {
        return 1;
    }

    template <typename First, typename ... Other>
    constexpr int product(First first, Other ... others)
    {
        return first * product(others...);
    }
};