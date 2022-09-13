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

#define MC_CONCAT_IMPL(s1, s2) s1##s2
#define MC_CONCAT(s1, s2)      MC_CONCAT_IMPL(s1, s2)

#ifndef MC_ANONYMOUS_VAR
#ifdef __COUNTER__
#if MC_HAS_FEATURE(modules)
#define MC_ANONYMOUS_VAR(str)                                                  \
    MC_CONCAT(MC_CONCAT(MC_CONCAT(str, __COUNTER__), _), __LINE__)
#else
#define MC_ANONYMOUS_VAR(str) MC_CONCAT(str, __COUNTER__)
#endif
#else
#define MC_ANONYMOUS_VAR(str) MC_CONCAT(str, __LINE__)
#endif
#endif

#if defined(_DEBUG)
#define MC_DEBUG
#endif

#if defined(NDEBUG)
#define MC_RELEASE
#endif

#if defined(MC_DEBUG) && defined(MC_RELEASE)
#error "Both debug & release mode defined"
#endif
