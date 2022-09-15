// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_integer_comparison_functions)

#include <utility>

namespace mc {
using std::cmp_equal;
using std::cmp_greater;
using std::cmp_greater_equal;
using std::cmp_less;
using std::cmp_less_equal;
using std::cmp_not_equal;
}  // namespace mc
#else

#include <type_traits>

namespace mc {

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_equal(T t, U u) noexcept  // NOLINT
    -> bool
{
    if constexpr (std::is_signed_v<T> and std::is_signed_v<U>) {
        return t == u;
    } else if (std::is_signed_v<T> and not std::is_signed_v<U>) {
        using UT = std::make_unsigned_t<T>;
        return t < 0 ? false : UT(t) == u;
    } else {
        static_assert(not std::is_signed_v<T> and not std::is_signed_v<U>);
        using UU = std::make_unsigned_t<U>;
        return u < 0 ? false : t == UU(u);
    }
}

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_not_equal(T t, U u) noexcept  // NOLINT
    -> bool
{
    return !cmp_equal(t, u);
}

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_less(T t, U u) noexcept  // NOLINT
    -> bool
{

    if constexpr (std::is_signed_v<T> and std::is_signed_v<U>) {
        return t < u;
    } else if (std::is_signed_v<T> and not std::is_signed_v<U>) {
        using UT = std::make_unsigned_t<T>;
        return t < 0 ? true : UT(t) < u;
    } else {
        static_assert(not std::is_signed_v<T> and not std::is_signed_v<U>);
        using UU = std::make_unsigned_t<U>;
        return u < 0 ? false : t < UU(u);
    }
}

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_greater(T t, U u) noexcept  // NOLINT
    -> bool
{
    return cmp_less(u, t);
}

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_less_equal(T t, U u) noexcept  // NOLINT
    -> bool
{
    return !cmp_greater(t, u);
}

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_greater_equal(T t, U u) noexcept  // NOLINT
    -> bool
{
    return !cmp_less(t, u);
}
}  // namespace mc
#endif
