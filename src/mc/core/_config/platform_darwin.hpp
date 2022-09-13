// SPDX-License-Identifier: BSL-1.0
#pragma once

#define CF_EXCLUDE_CSTD_HEADERS
#include <TargetConditionals.h>

// https://riptutorial.com/xcode/example/1219/targetconditionals
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define MC_PLATFORM_IPHONE
#define MC_PLATFORM_IOS
#else
#define MC_PLATFORM_MAC
#endif
