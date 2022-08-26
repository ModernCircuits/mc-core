// SPDX-License-Identifier: BSL-1.0
#pragma once

#define MC_COMPILER_GCC

#define MC_LIKELY(x)   __builtin_expect(x, 1)
#define MC_UNLIKELY(x) __builtin_expect(x, 0)

#define MC_FALLTHROUGH           __attribute__((fallthrough))
#define MC_ATTRIBUTE_UNUSED      __attribute__((__unused__))
#define MC_MAY_ALIAS             __attribute__((__may_alias__))
#define MC_UNREACHABLE_RETURN(x) __builtin_unreachable();
#define MC_NODISCARD             __attribute__((warn_unused_result))  // NOLINT

#define MC_FUNC_SIG __PRETTY_FUNCTION__

#if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#define MC_NO_CXX17_STRUCTURED_BINDINGS
#endif
#if !defined(__cpp_inline_variables) || (__cpp_inline_variables < 201606)
#define MC_NO_CXX17_INLINE_VARIABLES
#define MC_INLINE_VAR
#else
#define MC_INLINE_VAR inline
#endif
#if !defined(__cpp_fold_expressions) || (__cpp_fold_expressions < 201603)
#define MC_NO_CXX17_FOLD_EXPRESSIONS
#endif
#if !defined(__cpp_if_constexpr) || (__cpp_if_constexpr < 201606)
#define MC_NO_CXX17_IF_CONSTEXPR
#endif
