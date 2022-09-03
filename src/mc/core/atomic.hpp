// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <atomic>

namespace mc {
template<typename T>
using Atomic = std::atomic<T>;
}
