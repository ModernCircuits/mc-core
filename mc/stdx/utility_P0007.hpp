#pragma once

#include <utility>

#if defined(__cpp_lib_as_const)
namespace mc {
using std::as_const;
}
#else
#include "mc/preprocessor.hpp"
#include "mc/type_traits.hpp"
namespace mc {
template <typename T>
MC_NODISCARD constexpr auto as_const(T& t) noexcept -> std::add_const_t<T>&
{
    return t;
}
}
#endif