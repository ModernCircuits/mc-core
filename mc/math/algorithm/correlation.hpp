#pragma once

#include "mc/algorithm.hpp"
#include "mc/cmath.hpp"
#include "mc/iterator.hpp"

namespace mc {
namespace math {

template <typename InputIt1, typename InputIt2>
constexpr auto correlation(
    InputIt1 xf, InputIt1 xl, InputIt2 yf, InputIt2 yl) noexcept
    -> std::common_type_t<typename std::iterator_traits<InputIt1>::value_type,
        typename std::iterator_traits<InputIt2>::value_type>
{
    using T = std::common_type_t<
        typename std::iterator_traits<InputIt1>::value_type,
        typename std::iterator_traits<InputIt2>::value_type>;

    auto sumX       = T { 0 };
    auto sumY       = T { 0 };
    auto sumXY      = T { 0 };
    auto squareSumX = T { 0 };
    auto squareSumY = T { 0 };

    auto const n = std::min(std::distance(xf, xl), std::distance(yf, yl));
    for (auto i = std::ptrdiff_t { 0 }; i < n; ++i) {
        auto const xi = *std::next(xf, i);
        auto const yi = *std::next(yf, i);
        sumX += xi;
        sumY += yi;
        sumXY += xi * yi;
        squareSumX += xi * xi;
        squareSumY += yi * yi;
    }

    auto const a  = n * sumXY - sumX * sumY;
    auto const x1 = n * squareSumX - sumX * sumX;
    auto const y1 = n * squareSumY - sumY * sumY;

    return a / std::sqrt(x1 * y1);
}
} // namespace math
} // namespace mc