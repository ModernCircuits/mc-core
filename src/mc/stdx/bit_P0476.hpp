#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_bit_cast)
    #include <bit>
namespace mc {
using std::bit_cast;
}
#else
    #include <boost/core/bit.hpp>
namespace mc {
using boost::core::bit_cast;
} // namespace mc
#endif
