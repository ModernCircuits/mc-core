#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_int_pow2)

#include <bit>

namespace mc {

using std::bit_ceil;
using std::bit_floor;
using std::bit_width;
using std::has_single_bit;

}

#else

#include "mc/preprocessor.hpp"
#include "mc/stdx/bit_P0553.hpp"

namespace mc {

template <typename T>
MC_NODISCARD constexpr auto bit_width(T x) noexcept // NOLINT(readability-identifier-naming)
    -> std::enable_if_t<detail::BitUnsignedInt<T>, int>
{
    return std::numeric_limits<T>::digits - countl_zero(x);
}

namespace detail {
    template <typename T, bool NoPromotion>
    struct BitCeilImpl;

    template <typename T>
    struct BitCeilImpl<T, false> {
        static auto ceil(T x) noexcept -> T
        {
            unsigned const num   = std::numeric_limits<T>::digits - countl_zero(static_cast<T>(x - 1));
            unsigned const extra = std::numeric_limits<unsigned>::digits - std::numeric_limits<T>::digits;
            unsigned const ret   = 1U << (num + extra);
            return static_cast<T>(ret >> extra);
        }
    };

    template <typename T>
    struct BitCeilImpl<T, true> {
        static auto ceil(T x) noexcept -> T
        {
            unsigned const num = std::numeric_limits<T>::digits - countl_zero(static_cast<T>(x - 1U));
            return static_cast<T>(T { 1 } << num);
        }
    };
}

template <typename T>
MC_NODISCARD constexpr auto bit_ceil(T x) noexcept // NOLINT(readability-identifier-naming)
    -> std::enable_if_t<detail::BitUnsignedInt<T>, T>
{
    if (x < T(2)) {
        return T(1);
    }
    return detail::BitCeilImpl<T, !std::is_same<T, decltype(+x)>::value>::ceil(x);
}
} // namespace mc
#endif
