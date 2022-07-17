#pragma once

#if defined(__clang__)
    #include "mc/config/compiler_clang.hpp"
#elif defined(__GNUC__)
    #include "mc/config/compiler_gcc.hpp"
#elif defined(_MSC_VER)
    #include "mc/config/compiler_msvc.hpp"
#elif defined(__INTEL_COMPILER)
    #error "Compiler not yet supported"
#elif defined(__EMSCRIPTEN__)
    #error "Compiler not yet supported"
#else
    #error "Unknown compiler"
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include "mc/config/platform_win32.hpp"
#elif defined(__APPLE_CPP__) || defined(__APPLE_CC__)
    #include "mc/config/platform_darwin.hpp"
#elif defined(__linux__) && !defined(__ANDROID__)
    #include "mc/config/platform_linux.hpp"
#elif defined(__ANDROID__)
    #include "mc/config/platform_android.hpp"
#elif defined(__FreeBSD__) || (__OpenBSD__)
    #include "mc/config/platform_bsd.hpp"
#else
    #error "Unknown platform!"
#endif

#if defined(_DEBUG)
    #define MC_DEBUG 1
#endif

#if defined(NDEBUG)
    #define MC_RELEASE 1
#endif

#if defined(MC_DEBUG) && defined(MC_RELEASE)
    #error "Both debug & release mode defined"
#endif
