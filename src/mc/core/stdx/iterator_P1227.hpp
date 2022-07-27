// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_ssize)
    #include <iterator>
namespace mc {
using std::ssize;
}

#else
    #include <mc/core/type_traits.hpp>
namespace mc {
template <typename C>
MC_NODISCARD constexpr auto ssize(C const& c)
    -> std::common_type_t<std::ptrdiff_t, std::make_signed_t<decltype(c.size())> >
{
    using R = std::common_type_t<std::ptrdiff_t, std::make_signed_t<decltype(c.size())> >;
    return static_cast<R>(c.size());
}
template <typename T, std::size_t N>
MC_NODISCARD constexpr auto ssize(T const (&array)[N]) noexcept -> std::ptrdiff_t // NOLINT(*-avoid-c-arrays)
{
    (void)array;
    return static_cast<std::ptrdiff_t>(N);
}
} // namespace mc
#endif
