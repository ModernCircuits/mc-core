#pragma once

#include <utility>

#include "mc/preprocessor.hpp"
#include "mc/type_traits.hpp"

#if defined(__cpp_lib_integer_comparison_functions)
namespace mc {
using std::cmp_equal;
using std::cmp_greater;
using std::cmp_greater_equal;
using std::cmp_less;
using std::cmp_less_equal;
using std::cmp_not_equal;
}
#else
namespace mc {
namespace detail {
    template <typename T, typename U, bool IsSignedT, bool IsSignedU>
    struct IntegerCompareImpl;

    template <typename T, typename U>
    struct IntegerCompareImpl<T, U, true, true> {
        static auto equal(T t, U u) noexcept -> bool
        {
            return t == u;
        }
        static auto less(T t, U u) noexcept -> bool
        {
            return t < u;
        }
    };
    template <typename T, typename U>
    struct IntegerCompareImpl<T, U, true, false> {
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
    template <typename T, typename U>
    struct IntegerCompareImpl<T, U, false, false> {
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
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_equal(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    using cmp = detail::IntegerCompareImpl<T, U, std::is_signed<T>::value, std::is_signed<U>::value>;
    return cmp::equal(t, u);
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_not_equal(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    return !cmp_equal(t, u);
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_less(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    using cmp = detail::IntegerCompareImpl<T, U, std::is_signed<T>::value, std::is_signed<U>::value>;
    return cmp::less(t, u);
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_greater(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    return cmp_less(u, t);
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_less_equal(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    return !cmp_greater(t, u);
}

template <typename T, typename U>
MC_NODISCARD constexpr auto cmp_greater_equal(T t, U u) noexcept -> bool // NOLINT(readability-identifier-naming)
{
    return !cmp_less(t, u);
}
}
#endif