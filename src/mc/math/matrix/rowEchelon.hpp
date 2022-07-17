#pragma once

#include "mc/config.hpp"
#include "mc/math/algorithm/approx.hpp"
#include "mc/math/matrix/multiplyAddRow.hpp"
#include "mc/math/traits/IsMatrix.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto rowEchelon(Matrix& mat) -> std::enable_if_t<IsMatrix<Matrix>::value, void>
{
    if (mat.cols() < mat.rows()) {
        throw std::invalid_argument("matrix must have at least have as many columns as rows");
    }

    using size_type = typename Matrix::size_type;
    using T         = typename Matrix::value_type;

    static constexpr auto maxLoopCount = size_type { 100 };

    auto count     = size_type { 0 };
    auto completed = false;

    auto cRow = size_type {};
    auto cCol = size_type {};

    while ((!completed) && (count < maxLoopCount)) {
        for (auto diagIdx = size_type { 0 }; diagIdx < mat.rows(); ++diagIdx) {
            cRow = diagIdx;
            cCol = diagIdx;

            for (auto rowIdx = cRow + 1; rowIdx < mat.rows(); ++rowIdx) {
                if (!approx(mat(rowIdx, cCol), T {})) {
                    auto const rowOneIndex  = cCol;
                    auto const rowOneValue  = mat(rowOneIndex, cCol);
                    auto const currentValue = mat(rowIdx, cCol);
                    if (!approx(rowOneValue, T {})) {
                        auto const correction = -(currentValue / rowOneValue);
                        multiplyAddRow(mat, rowOneIndex, rowIdx, correction);
                    }
                }
            }
        }

        completed = isRowEchelon(mat);
        count += 1;
    }
}
} // namespace math
} // namespace mc
