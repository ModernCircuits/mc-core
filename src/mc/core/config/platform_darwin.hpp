// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <TargetConditionals.h>

// https://riptutorial.com/xcode/example/1219/targetconditionals
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define MC_IPHONE 1
#define MC_IOS 1
#else
#define MC_MAC 1
#endif
