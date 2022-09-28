// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_byteswap)
#include <bit>

namespace mc {
using std::byteswap;
}
#else
#include <mc/core/_bit/bit_cast.hpp>
#include <mc/core/_cstddef/byte.hpp>

#include <algorithm>
#include <array>

#include <type_traits>

namespace mc {
template<typename T>
[[nodiscard]] constexpr auto byteswap(T value) noexcept
    -> std::enable_if_t<std::is_integral_v<T>, T>
{
    static_assert(std::has_unique_object_representations_v<T>);
    auto raw = bit_cast<std::array<Byte, sizeof(T)> >(value);
    std::reverse(raw.begin(), raw.end());
    return bit_cast<T>(raw);
}
}  // namespace mc

#endif
