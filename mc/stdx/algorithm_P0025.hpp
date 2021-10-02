#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_clamp)
#include <algorithm>
namespace mc {
using std::clamp;
}
#else
#include "mc/preprocessor.hpp"
namespace mc {
template <typename T, typename Compare>
MC_NODISCARD constexpr auto clamp(T const& v, T const& lo, T const& hi, Compare comp) -> T const&
{
    if (comp(hi, v)) {
        return hi;
    }
    if (comp(v, lo)) {
        return lo;
    }
    return v;
}

template <typename T>
MC_NODISCARD constexpr auto clamp(T const& v, T const& lo, T const& hi) -> T const&
{
    return clamp(v, lo, hi, [](auto const& l, auto const& r) { return l < r; });
}
} // namespace mc
#endif