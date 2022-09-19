// SPDX-License-Identifier: BSL-1.0
#pragma once

#define MC_COMPILER_GCC

#define MC_LIKELY(x)   __builtin_expect(x, 1)
#define MC_UNLIKELY(x) __builtin_expect(x, 0)

#define MC_FALLTHROUGH           __attribute__((fallthrough))
#define MC_ATTRIBUTE_UNUSED      __attribute__((__unused__))
#define MC_MAY_ALIAS             __attribute__((__may_alias__))
#define MC_UNREACHABLE_RETURN(x) __builtin_unreachable();
#define MC_FUNC_SIG              __PRETTY_FUNCTION__
#define MC_NO_INLINE             __attribute__((noinline))
#define MC_COLD                  __attribute__((cold))
