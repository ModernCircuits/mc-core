#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_bitops)
#include <bit>
namespace mc {
using std::countl_one;
using std::countl_zero;
using std::countr_one;
using std::countr_zero;
using std::popcount;
using std::rotl;
using std::rotr;
}
#else

#include "mc/limits.hpp"
#include "mc/preprocessor.hpp"
#include "mc/type_traits.hpp"

namespace mc {

namespace detail {
    // clang-format off
    template <typename T>
    constexpr auto bitUnsignedInt = std::is_same<T, unsigned char>::value
                                 || std::is_same<T, unsigned short>::value
                                 || std::is_same<T, unsigned int>::value
                                 || std::is_same<T, unsigned long>::value
                                 || std::is_same<T, unsigned long long>::value;
    // clang-format on
} // namespace detail

template <typename T>
MC_NODISCARD constexpr auto countl_zero(T x) noexcept // NOLINT(readability-identifier-naming)
    -> std::enable_if_t<detail::bitUnsignedInt<T>, int>
{
    auto const totalBits = std::numeric_limits<T>::digits;
    if (x == T(0)) {
        return std::numeric_limits<T>::digits;
    }
    auto res = 0;
    while (!(x & (T(1) << (static_cast<T>(totalBits) - T(1))))) {
        x = static_cast<T>(x << T(1));
        ++res;
    }
    return res;
}
} // namespace mc
#endif
