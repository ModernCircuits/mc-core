// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <exception>

#if defined(__cpp_lib_uncaught_exceptions)
namespace mc {
using std::uncaught_exceptions;
}
#else
    #include <boost/core/uncaught_exceptions.hpp>
namespace mc {
using boost::core::uncaught_exceptions;
}
#endif
