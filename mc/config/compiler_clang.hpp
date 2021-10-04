#pragma once

#ifndef __has_extension
    #define __has_extension __has_feature
#endif

#ifndef __has_attribute
    #define __has_attribute(x) 0
#endif

#ifndef __has_cpp_attribute
    #define __has_cpp_attribute(x) 0
#endif

#define MC_COMPILER_CLANG 1

#define MC_LIKELY(x) __builtin_expect(x, 1)
#define MC_UNLIKELY(x) __builtin_expect(x, 0)

#define MC_FALLTHROUGH [[clang::fallthrough]]
#define MC_ATTRIBUTE_UNUSED __attribute__((__unused__))
#define MC_MAY_ALIAS __attribute__((__may_alias__))
#define MC_UNREACHABLE_RETURN(x) __builtin_unreachable();
#define MC_NODISCARD __attribute__((warn_unused_result)) // NOLINT

#define MC_FUNC_SIG __PRETTY_FUNCTION__

#if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
    #define MC_NO_CXX17_STRUCTURED_BINDINGS
#endif

#if !defined(__cpp_if_constexpr) || (__cpp_if_constexpr < 201606)
    #define MC_NO_CXX17_IF_CONSTEXPR
#endif

// Clang 3.9+ in c++1z
#if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
    #define MC_NO_CXX17_INLINE_VARIABLES
    #define MC_NO_CXX17_FOLD_EXPRESSIONS
    #define MC_INLINE_VAR
#else
    #define MC_INLINE_VAR inline
#endif
