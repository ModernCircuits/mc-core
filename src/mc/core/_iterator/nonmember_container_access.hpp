// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_nonmember_container_access)

#include <iterator>

namespace mc {
using std::data;
using std::empty;
using std::size;
}  // namespace mc

#else
#include <mc/core/initializer_list.hpp>
#include <mc/core/type_traits.hpp>

namespace mc {

// NOLINTBEGIN(*-avoid-c-arrays)

template<typename C>
[[nodiscard]] constexpr auto size(C const& c) -> decltype(c.size())
{
    return c.size();
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto size(T const (&array)[N]) noexcept -> std::size_t
{
    (void)array;
    return N;
}

template<typename C>
[[nodiscard]] constexpr auto data(C& c) -> decltype(c.data())
{
    return c.data();
}

template<typename C>
[[nodiscard]] constexpr auto data(C const& c) -> decltype(c.data())
{
    return c.data();
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto data(T (&array)[N]) noexcept -> T*
{
    return array;  // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}

template<typename E>
[[nodiscard]] constexpr auto data(std::initializer_list<E> il) noexcept
    -> E const*
{
    return il.begin();
}

template<typename C>
[[nodiscard]] constexpr auto empty(const C& c) -> decltype(c.empty())
{
    return c.empty();
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto empty(const T (&array)[N]) noexcept -> bool
{
    (void)array;
    return false;
}

template<typename E>
[[nodiscard]] constexpr auto empty(std::initializer_list<E> il) noexcept -> bool
{
    return il.size() == 0;
}

// NOLINTEND(*-avoid-c-arrays)

}  // namespace mc
#endif
