#pragma once

#include "mc/config.hpp"

#include "mc/math/algorithm/approx.hpp"
#include "mc/math/matrix/findRowWithMaxElement.hpp"
#include "mc/math/matrix/isSquare.hpp"
#include "mc/math/matrix/join.hpp"
#include "mc/math/matrix/makeIdentity.hpp"
#include "mc/math/matrix/multiplyAddRow.hpp"
#include "mc/math/matrix/multiplyRow.hpp"
#include "mc/math/matrix/splitColumns.hpp"

namespace mc {
namespace math {

template <typename Matrix>
auto isEqual(Matrix const& l, Matrix const& r) -> bool
{
    if ((l.rows() != r.rows()) || (l.cols() != r.cols())) { return false; }
    auto cmp = [](auto a, auto b) { return approx(a, b); };
    for (decltype(l.rows()) row = 0; row < l.rows(); ++row) {
        for (decltype(l.cols()) col = 0; col < l.cols(); ++col) {
            if (!cmp(l(row, col), r(row, col))) { return false; }
        }
    }
    return true;
}

template <typename Matrix>
auto inverse(Matrix const& mat) -> Matrix
{
    using size_type = typename Matrix::size_type;
    using T         = typename Matrix::value_type;

    if (!isSquare(mat)) {
        throw std::invalid_argument("matrix must be square");
    }

    static constexpr auto maxLoopCount = size_type { 100 };

    auto const identity = makeIdentity<Matrix>(mat.rows());
    auto augment        = join(mat, identity);

    auto count     = size_type { 0 };
    auto completed = false;

    auto cRow = size_type {};
    auto cCol = size_type {};

    auto result = Matrix { mat.rows(), mat.cols() };
    while ((!completed) && (count < maxLoopCount)) {
        for (auto diagIdx = size_type { 0 }; diagIdx < augment.rows();
             ++diagIdx) {
            cRow = diagIdx;
            cCol = diagIdx;

            auto maxRowIdx = findRowWithMaxElement(augment, cCol, cRow);
            if (maxRowIdx != cRow) { swapRow(augment, cRow, maxRowIdx); }

            if (augment(cRow, cCol) != T { 1 }) {
                auto factor = T { 1 } / augment(cRow, cCol);
                multiplyRow(augment, cRow, factor);
            }

            for (auto rowIdx = cRow + 1; rowIdx < augment.rows(); ++rowIdx) {
                auto rowOneIndex  = cCol;
                auto currentValue = augment(rowIdx, cCol);
                auto rowOneValue  = augment(rowOneIndex, cCol);

                if (!approx(rowOneValue, T {})) {
                    auto correction = -(currentValue / rowOneValue);
                    multiplyAddRow(augment, rowOneIndex, rowIdx, correction);
                }
            }

            for (auto colIdx = cCol + 1; colIdx < mat.cols(); ++colIdx) {
                if (!approx(augment(cRow, colIdx), T {})) {
                    auto rowOneIndex  = colIdx;
                    auto currentValue = augment(cRow, colIdx);
                    auto rowOneValue  = augment(rowOneIndex, colIdx);

                    if (!approx(rowOneValue, T {})) {
                        auto correction = -(currentValue / rowOneValue);
                        multiplyAddRow(augment, rowOneIndex, cRow, correction);
                    }
                }
            }
        }

        auto splits = splitColumns(augment, mat.cols());
        if (isEqual(splits.first, identity)) {
            completed = true;
            result    = splits.second;
        }

        count += 1;
    }

    return result;
}
} // namespace math
} // namespace mc