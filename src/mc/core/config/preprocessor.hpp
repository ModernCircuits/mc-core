// SPDX-License-Identifier: BSL-1.0

#pragma once

#if defined(__has_builtin)
#define MC_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
#define MC_HAS_BUILTIN(...) 0
#endif

#if defined(__has_feature)
#define MC_HAS_FEATURE(...) __has_feature(__VA_ARGS__)
#else
#define MC_HAS_FEATURE(...) 0
#endif

#ifndef MC_ANONYMOUS_VARIABLE
#define MC_CONCATENATE_IMPL(s1, s2) s1##s2
#define MC_CONCATENATE(s1, s2) MC_CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
#if MC_HAS_FEATURE(modules)
#define MC_ANONYMOUS_VARIABLE(str)                                                                   \
    MC_CONCATENATE(MC_CONCATENATE(MC_CONCATENATE(str, __COUNTER__), _), __LINE__)
#else
#define MC_ANONYMOUS_VARIABLE(str) MC_CONCATENATE(str, __COUNTER__)
#endif
#else
#define MC_ANONYMOUS_VARIABLE(str) MC_CONCATENATE(str, __LINE__)
#endif
#endif

#if (defined(MC_COMPILER_GCC) || defined(MC_COMPILER_CLANG)) && !defined(MC_MAC)
#ifndef MC_ALIGNAS
#define MC_ALIGNAS(bytes) __attribute__((aligned(bytes)))
#endif
#elif defined(MC_COMPILER_MSVC)
#ifndef MC_ALIGNAS
#define MC_ALIGNAS(bytes) __declspec(align(bytes))
#endif
#else
#define MC_ALIGNAS(bytes)
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
