// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(MC_COMPILER_MSVC)
#pragma warning(push)
#pragma warning(disable: 4702)  // unreachable code
#endif

#include <moodycamel/concurrentqueue.h>
#include <readerwriterqueue/readerwritercircularbuffer.h>
#include <readerwriterqueue/readerwriterqueue.h>

#if defined(MC_COMPILER_MSVC)
#pragma warning(pop)
#endif

namespace mc {
template<typename T>
using LockFreeQueue = moodycamel::ConcurrentQueue<T>;
}
