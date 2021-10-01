#pragma once

#include <iterator>
#include <type_traits>

#include "mc/preprocessor.hpp"

#if defined(__cpp_lib_ssize)
namespace mc {
using std::ssize;
}
#else
namespace mc {
template <typename C>
MC_NODISCARD constexpr auto ssize(C const& c)
    -> std::common_type_t<std::ptrdiff_t,
        std::make_signed_t<decltype(c.size())> >
{
    using R = std::common_type_t<std::ptrdiff_t,
        std::make_signed_t<decltype(c.size())> >;
    return static_cast<R>(c.size());
}
template <typename T, std::ptrdiff_t N>
MC_NODISCARD constexpr auto ssize(T const (&array)[N]) noexcept -> std::ptrdiff_t
{
    (void)array;
    return N;
}
} // namespace mc
#endif