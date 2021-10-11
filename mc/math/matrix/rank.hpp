#pragma once

#include "mc/math/matrix/determinant.hpp"
#include "mc/math/matrix/isNonZero.hpp"
#include "mc/math/matrix/isRowEchelon.hpp"
#include "mc/math/matrix/rowEchelon.hpp"
#include "mc/math/matrix/subMatrix.hpp"
#include "mc/math/traits/IsMatrix.hpp"
#include "mc/stdexcept.hpp"
#include "mc/vector.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto rank(Matrix const& mat)
    -> std::enable_if_t<IsMatrix<Matrix>::value, typename Matrix::size_type>
{
    using T         = typename Matrix::value_type;
    using size_type = typename Matrix::size_type;

    auto copy = Matrix { mat };
    rowEchelon(copy);

    auto numNonZeroRows = size_type {};
    if (!isRowEchelon(copy)) {
        auto subMatricies = std::vector<Matrix> {};
        subMatricies.push_back(mat);

        auto completed             = false;
        auto subDynamicMatrixCount = size_type {};
        while ((subDynamicMatrixCount < subMatricies.size()) && (!completed)) {
            auto const cur = subMatricies[subDynamicMatrixCount];
            subDynamicMatrixCount++;

            if (isNonZero(cur)) {
                if (!approx(determinant(cur), T {})) {
                    completed      = true;
                    numNonZeroRows = cur.rows();
                } else {
                    if ((cur.rows() > 2) && (cur.cols() > 2)) {
                        for (auto i = size_type { 0 }; i < cur.rows(); ++i) {
                            for (auto j = size_type { 0 }; j < cur.cols();
                                 ++j) {
                                auto sub = subMatrix(cur, i, j);
                                subMatricies.push_back(sub);
                            }
                        }
                    }
                }
            }
        }
    } else {
        for (auto row = size_type { 0 }; row < copy.rows(); ++row) {
            auto colSum = size_type {};
            for (decltype(copy.cols()) col = 0; col < copy.cols(); ++col) {
                if (!approx(copy(row, col), T {})) { colSum++; }
            }

            if (colSum > 0) { numNonZeroRows++; }
        }
    }

    return numNonZeroRows;
}
} // namespace math
} // namespace mc