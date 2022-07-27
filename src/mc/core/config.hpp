// SPDX-License-Identifier: BSL-1.0

#pragma once

#if __has_include(<version>)
    #include <version>
#else
    #error "mc-core expects <version> to be available"
#endif

#if defined(__clang__)
    #include <mc/core/config/compiler_clang.hpp>
#elif defined(__GNUC__)
    #include <mc/core/config/compiler_gcc.hpp>
#elif defined(_MSC_VER)
    #include <mc/core/config/compiler_msvc.hpp>
#elif defined(__INTEL_COMPILER)
    #error "Compiler not yet supported"
#elif defined(__EMSCRIPTEN__)
    #error "Compiler not yet supported"
#else
    #error "Unknown compiler"
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include <mc/core/config/platform_win32.hpp>
#elif defined(__APPLE_CPP__) || defined(__APPLE_CC__)
    #include <mc/core/config/platform_darwin.hpp>
#elif defined(__linux__) && !defined(__ANDROID__)
    #include <mc/core/config/platform_linux.hpp>
#elif defined(__ANDROID__)
    #include <mc/core/config/platform_android.hpp>
#elif defined(__FreeBSD__) || (__OpenBSD__)
    #include <mc/core/config/platform_bsd.hpp>
#else
    #error "Unknown platform!"
#endif

#include <mc/core/config/preprocessor.hpp>

#if defined(MC_NAMESPACE_ALIAS)
namespace MC_NAMESPACE_ALIAS = mc;
#endif
