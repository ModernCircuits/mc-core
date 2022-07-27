#pragma once

#include <moodycamel/concurrentqueue.h>
#include <readerwriterqueue/readerwritercircularbuffer.h>
#include <readerwriterqueue/readerwriterqueue.h>

namespace mc {
template <typename T>
using LockFreeQueue = moodycamel::ConcurrentQueue<T>;
}
