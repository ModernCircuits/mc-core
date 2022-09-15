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
namespace detail {
template<typename T, typename U, bool IsSignedT, bool IsSignedU>
struct IntegerCompareImpl;

template<typename T, typename U>
struct IntegerCompareImpl<T, U, true, true>
{
    static auto equal(T t, U u) noexcept -> bool { return t == u; }

    static auto less(T t, U u) noexcept -> bool { return t < u; }
};

template<typename T, typename U>
struct IntegerCompareImpl<T, U, true, false>
{
    using UT = std::make_unsigned_t<T>;

    static auto equal(T t, U u) noexcept -> bool
    {
        return t < 0 ? false : UT(t) == u;
    }

    static auto less(T t, U u) noexcept -> bool
    {
        return t < 0 ? true : UT(t) < u;
    }
};

template<typename T, typename U>
struct IntegerCompareImpl<T, U, false, false>
{
    using UU = std::make_unsigned_t<U>;

    static auto equal(T t, U u) noexcept -> bool
    {
        return u < 0 ? false : t == UU(u);
    }

    static auto less(T t, U u) noexcept -> bool
    {
        return u < 0 ? false : t < UU(u);
    }
};
}  // namespace detail

template<typename T, typename U>
[[nodiscard]] constexpr auto cmp_equal(T t, U u) noexcept  // NOLINT
    -> bool
{
    using cmp = detail::IntegerCompareImpl<
        T,
        U,
        std::is_signed<T>::value,
        std::is_signed<U>::value>;
    return cmp::equal(t, u);
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
    using cmp = detail::IntegerCompareImpl<
        T,
        U,
        std::is_signed<T>::value,
        std::is_signed<U>::value>;
    return cmp::less(t, u);
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
