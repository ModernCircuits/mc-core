// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <type_traits>

#if defined(__cpp_lib_void_t)
namespace mc {
using std::void_t;
}
#else
namespace mc {
template <typename...>
using void_t = void;
}
#endif
