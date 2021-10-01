#pragma once

#include <algorithm>

#if __cplusplus > 201402L
namespace mc {
using std::for_each_n;
}
#else

#include "mc/preprocessor.hpp"

namespace mc {
template <typename InputIt, typename Size, typename UnaryFunction>
constexpr auto for_each_n(InputIt first, Size n, UnaryFunction f) -> InputIt
{
    for (Size i = 0; i < n; ++first, (void)++i) {
        f(*first);
    }
    return first;
}
} // namespace mc

#endif