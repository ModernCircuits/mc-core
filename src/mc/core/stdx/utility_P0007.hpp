#pragma once

#include "mc/core/version.hpp"

#if defined(__cpp_lib_as_const)

    #include <utility>

namespace mc {
using std::as_const;
}

#else

    #include "mc/core/preprocessor.hpp"
    #include "mc/core/type_traits.hpp"

namespace mc {
template <typename T>
MC_NODISCARD constexpr auto as_const(T& t) noexcept // NOLINT
    -> std::add_const_t<T>&
{
    return t;
}
} // namespace mc

#endif
