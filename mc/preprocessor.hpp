#pragma once

#if defined(_MSC_VER)
#define MC_NODISCARD _Check_return_
#else
#define MC_NODISCARD __attribute__((warn_unused_result)) // NOLINT
#endif