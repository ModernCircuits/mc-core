#pragma once

#include "mc/config.hpp"

namespace mc {
namespace math {
namespace detail {
template <typename SizeType>
MC_NODISCARD constexpr auto matrixSubscriptToIndex(
    SizeType row, SizeType col, SizeType numColumns) noexcept -> SizeType
{
    return (row * numColumns) + col;
}
} // namespace detail
} // namespace math
} // namespace mc