// SPDX-License-Identifier: BSL-1.0

#pragma once

#define MC_COMPILER_MSVC 1

#define MC_LIKELY(x)
#define MC_UNLIKELY(x)

#define MC_FALLTHROUGH
#define MC_ATTRIBUTE_UNUSED
#define MC_MAY_ALIAS
#define MC_UNREACHABLE_RETURN(x)
#define MC_NODISCARD _Check_return_

#define MC_FUNC_SIG __FUNCSIG__

#if (_MSC_VER < 1911) || (_MSVC_LANG < 201703)
    #define MC_NO_CXX17_STRUCTURED_BINDINGS
    #define MC_NO_CXX17_IF_CONSTEXPR
#endif

#if (_MSC_VER < 1912) || (_MSVC_LANG < 201703)
    #define MC_NO_CXX17_INLINE_VARIABLES
    #define MC_NO_CXX17_FOLD_EXPRESSIONS
    #define MC_INLINE_VAR
#else
    #define MC_INLINE_VAR inline
#endif
