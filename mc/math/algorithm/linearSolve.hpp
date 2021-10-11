#pragma once

#include "mc/math/dense/DynamicMatrix.hpp"
#include "mc/math/dense/DynamicVector.hpp"

#include "mc/config.hpp"

namespace mc {
namespace math {

/// INTERFACE
/////////////////////////////////////////////////////////////////////////
enum class LinearSolveSolution {
    None,
    NoUnique,
    Unique,
};

template <typename T>
struct LinearSolveResult {
    LinearSolveSolution success;
    DynamicVector<T> vec;
};

template <typename T>
MC_NODISCARD auto linearSolve(DynamicMatrix<T> const& a,
    DynamicVector<T> const& b) -> LinearSolveResult<T>;

/// IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////
template <typename T>
auto linearSolve(DynamicMatrix<T> const& a, DynamicVector<T> const& b)
    -> LinearSolveResult<T>
{
    using ssize_type = std::make_signed_t<decltype(a.size())>;

    auto const inputRank = rank(a);

    auto bMat = DynamicMatrix<T> { b.size(), 1 };
    for (decltype(b.size()) row { 0 }; row < b.size(); ++row) {
        bMat(row, 0) = b[row];
    }

    auto augmented = join(a, bMat);
    rowEchelon(augmented);
    auto const augmentedRank = rank(augmented);
    auto const solution      = [&] {
        if ((inputRank == augmentedRank) && (inputRank < a.rows())) {
            return LinearSolveSolution::NoUnique;
        }
        if (inputRank < augmentedRank) { return LinearSolveSolution::None; }
        return LinearSolveSolution::Unique;
    }();

    auto result
        = LinearSolveResult<T> { solution, DynamicVector<T> { b.size() } };
    auto const numRows  = static_cast<ssize_type>(augmented.rows());
    auto const numCols  = static_cast<ssize_type>(augmented.cols());
    auto const startRow = static_cast<ssize_type>(numRows - 1);

    for (auto i = startRow; i >= 0; --i) {
        auto const currentResult = augmented(i, numCols - 1);

        auto sum = T {};
        for (auto j = i + 1; j < numRows; ++j) {
            sum += (augmented(i, j) * result.vec[j]);
        }

        result.vec[i] = (currentResult - sum) / augmented(i, i);
    }

    return result;
}

} // namespace math
} // namespace mc