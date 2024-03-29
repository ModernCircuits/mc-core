// SPDX-License-Identifier: BSL-1.0
#pragma once

#if __has_include(<version>)
#include <version>
#else
#error "mc-core expects <version> to be available"
#endif

#if defined(__clang__)
#include <mc/core/_config/compiler_clang.hpp>
#elif defined(__GNUC__)
#include <mc/core/_config/compiler_gcc.hpp>
#elif defined(_MSC_VER)
#include <mc/core/_config/compiler_msvc.hpp>
#elif defined(__INTEL_COMPILER)
#error "Compiler not yet supported"
#else
#error "Unknown compiler"
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <mc/core/_config/platform_win32.hpp>
#elif defined(__APPLE_CPP__) || defined(__APPLE_CC__)
#include <mc/core/_config/platform_darwin.hpp>
#elif defined(__linux__) && !defined(__ANDROID__)
#include <mc/core/_config/platform_linux.hpp>
#elif defined(__ANDROID__)
#include <mc/core/_config/platform_android.hpp>
#elif defined(__FreeBSD__) || (__OpenBSD__)
#include <mc/core/_config/platform_bsd.hpp>
#elif defined(__EMSCRIPTEN__)
#include <mc/core/_config/platform_emscripten.hpp>
#else
#error "Unknown platform!"
#endif

#include <mc/core/_config/debug_break.hpp>
#include <mc/core/_config/documentation.hpp>
#include <mc/core/_config/preprocessor.hpp>
#include <mc/core/_config/thread_safety_attributes.hpp>

#if defined(__cpp_if_consteval)
#define MC_IF_CONSTEVAL if consteval
#else
#define MC_IF_CONSTEVAL if (__builtin_is_constant_evaluated())
#endif

#if defined(MC_NAMESPACE_ALIAS)
namespace MC_NAMESPACE_ALIAS = mc;
#endif
