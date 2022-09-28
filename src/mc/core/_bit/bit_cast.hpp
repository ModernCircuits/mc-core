// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_bit_cast)
#include <bit>

namespace mc {
using std::bit_cast;
}
#else
// Boost via Emscripten is at 1.75. Bit header missing
#if __has_include(<boost/core/bit.hpp>)
#include <boost/core/bit.hpp>

namespace mc {
using boost::core::bit_cast;
}  // namespace mc

#else

#include <cstring>

#include <type_traits>

namespace mc {
template<typename To, typename From>
[[nodiscard]] auto bit_cast(From const& src) noexcept  // NOLINT
    -> std::enable_if_t<                               //
        sizeof(To) == sizeof(From)                     //
            && std::is_trivially_copyable_v<From>      //
            && std::is_trivially_copyable_v<To>,       //
        To>
{
    static_assert(
        std::is_trivially_constructible_v<To>,
        "This implementation additionally requires "
        "destination type to be trivially constructible"
    );

    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}
}  // namespace mc
#endif
#endif
