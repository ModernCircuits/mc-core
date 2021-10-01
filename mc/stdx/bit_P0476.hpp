#pragma once

#if __has_include(<bit>) && __cplusplus > 201703L
#include <bit>
#endif

#include "mc/preprocessor.hpp"

#if defined(__cpp_lib_bit_cast)
namespace mc {
using std::bit_cast;
}
#else
namespace mc {

} // namespace mc
#endif
