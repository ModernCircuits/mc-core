#pragma once

#include <type_traits>

#if defined(__cpp_lib_bool_constant)
namespace mc {
using std::bool_constant;
}
#else
namespace mc {
template <bool B>
using bool_constant = integral_constant<bool, B>;
}
#endif