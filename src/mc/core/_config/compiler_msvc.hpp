// SPDX-License-Identifier: BSL-1.0
#pragma once

#define MC_COMPILER_MSVC

#define MC_LIKELY(x)
#define MC_UNLIKELY(x)

#define MC_FALLTHROUGH
#define MC_ATTRIBUTE_UNUSED
#define MC_MAY_ALIAS
#define MC_UNREACHABLE_RETURN(x)
#define MC_NODISCARD _Check_return_

#define MC_FUNC_SIG __FUNCSIG__

#define MC_INLINE_VAR inline
