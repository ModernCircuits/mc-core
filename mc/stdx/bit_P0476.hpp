#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_bit_cast)
#include <bit>
namespace mc {
using std::bit_cast;
}
#else
namespace mc {

} // namespace mc
#endif
