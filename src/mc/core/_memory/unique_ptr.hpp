// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <memory>

namespace mc {

template<typename T, typename Deleter = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T, Deleter>;

template<typename T, typename... Args>
auto makeUnique(Args&&... args) -> UniquePtr<T>
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

}  // namespace mc
