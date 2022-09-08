// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <memory>

namespace mc {

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T, typename... Args>
auto makeShared(Args&&... args) -> SharedPtr<T>
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
}  // namespace mc
