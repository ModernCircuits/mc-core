// SPDX-License-Identifier: BSL-1.0

#pragma once

#define MC_WINDOWS 1

#ifdef _WIN64
    #define MC_64BIT 1
#else
    #define MC_32BIT 1
#endif
