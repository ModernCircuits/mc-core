// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_nonmember_container_access)

    #include <iterator>

namespace mc {
using std::data;
using std::empty;
using std::size;
} // namespace mc

#else
    #include <mc/core/initializer_list.hpp>
    #include <mc/core/type_traits.hpp>
namespace mc {

template <typename C>
MC_NODISCARD constexpr auto size(C const& c) -> decltype(c.size())
{
    return c.size();
}
template <typename T, std::size_t N>
MC_NODISCARD constexpr auto size(T const (&array)[N]) noexcept -> std::size_t // NOLINT(*-avoid-c-arrays)
{
    (void)array;
    return N;
}

template <typename C>
MC_NODISCARD constexpr auto data(C& c) -> decltype(c.data())
{
    return c.data();
}

template <typename C>
MC_NODISCARD constexpr auto data(C const& c) -> decltype(c.data())
{
    return c.data();
}

template <typename T, std::size_t N>
MC_NODISCARD constexpr auto data(T (&array)[N]) noexcept -> T* // NOLINT(*-avoid-c-arrays)
{
    return array; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}

template <typename E>
MC_NODISCARD constexpr auto data(std::initializer_list<E> il) noexcept -> E const*
{
    return il.begin();
}

template <typename C>
MC_NODISCARD constexpr auto empty(const C& c) -> decltype(c.empty())
{
    return c.empty();
}

template <typename T, std::size_t N>
MC_NODISCARD constexpr auto empty(const T (&array)[N]) noexcept -> bool // NOLINT(*-avoid-c-arrays)
{
    (void)array;
    return false;
}

template <typename E>
MC_NODISCARD constexpr auto empty(std::initializer_list<E> il) noexcept -> bool
{
    return il.size() == 0;
}
} // namespace mc
#endif
