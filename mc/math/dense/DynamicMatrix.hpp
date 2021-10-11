#pragma once

#include "mc/math/matrix/findRowWithMaxElement.hpp"
#include "mc/math/matrix/inverse.hpp"
#include "mc/math/matrix/isNonZero.hpp"
#include "mc/math/matrix/isRowEchelon.hpp"
#include "mc/math/matrix/isSquare.hpp"
#include "mc/math/matrix/join.hpp"
#include "mc/math/matrix/makeIdentity.hpp"
#include "mc/math/matrix/multiplyAddRow.hpp"
#include "mc/math/matrix/multiplyRow.hpp"
#include "mc/math/matrix/splitColumns.hpp"
#include "mc/math/matrix/swapRow.hpp"

#include "mc/math/matrix/detail/matrixAdd.hpp"
#include "mc/math/matrix/detail/matrixCompare.hpp"
#include "mc/math/matrix/detail/matrixMultiply.hpp"
#include "mc/math/matrix/detail/matrixStream.hpp"
#include "mc/math/matrix/detail/matrixSubscriptToIndex.hpp"
#include "mc/math/matrix/detail/matrixSubtract.hpp"

#include "mc/math/algorithm/linearSolve.hpp"
#include "mc/math/dense/DynamicVector.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/size.hpp"

#include "mc/algorithm.hpp"
#include "mc/config.hpp"
#include "mc/cstddef.hpp"
#include "mc/cstdint.hpp"
#include "mc/iostream.hpp"
#include "mc/iterator.hpp"
#include "mc/memory.hpp"
#include "mc/vector.hpp"

namespace mc {
namespace math {

template <typename T>
struct DynamicMatrix {
    using value_type = T;
    using size_type  = std::uint32_t;

    DynamicMatrix() noexcept = default;
    DynamicMatrix(size_type rows, size_type cols);
    DynamicMatrix(DynamicMatrix<T> const& other);

    auto operator=(DynamicMatrix<T> const& other) -> DynamicMatrix<T>&;

    auto clear() noexcept -> void;
    auto resize(size_type rows, size_type cols) -> void;

    MC_NODISCARD auto empty() const noexcept -> bool;
    MC_NODISCARD auto size() const noexcept -> size_type;
    MC_NODISCARD auto rows() const noexcept -> size_type;
    MC_NODISCARD auto cols() const noexcept -> size_type;

    MC_NODISCARD auto at(size_type row, size_type col) -> T&;
    MC_NODISCARD auto at(size_type row, size_type col) const -> T const&;

    MC_NODISCARD auto operator()(size_type row, size_type col) -> T&;
    MC_NODISCARD auto operator()(size_type row, size_type col) const
        -> T const&;

private:
    std::unique_ptr<T[]> data_ { nullptr }; // NOLINT
    size_type numRows_ {};
    size_type numCols_ {};
};

template <typename T>
auto operator==(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool;

template <typename T>
auto operator!=(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool;

template <typename T>
auto operator+(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
    -> DynamicMatrix<T>;

template <typename T>
auto operator+(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>;

template <typename T>
auto operator+(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>;

template <typename T>
auto operator-(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
    -> DynamicMatrix<T>;

template <typename T>
auto operator-(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>;

template <typename T>
auto operator-(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>;

template <typename T>
auto operator*(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
    -> DynamicMatrix<T>;

template <typename T>
auto operator*(DynamicMatrix<T> const& mat, DynamicVector<T> const& vec)
    -> DynamicVector<T>;

template <typename T>
auto operator*(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>;

template <typename T>
auto operator*(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>;

template <typename T>
auto operator<<(std::ostream& out, DynamicMatrix<T> const& mat)
    -> std::ostream&;

template <typename T>
auto subDynamicMatrix(DynamicMatrix<T> const& mat,
    typename DynamicMatrix<T>::size_type rowIdx,
    typename DynamicMatrix<T>::size_type colIdx) -> DynamicMatrix<T>;

template <typename T>
auto determinant(DynamicMatrix<T> const& mat) ->
    typename DynamicMatrix<T>::value_type;

template <typename T>
auto rowEchelon(DynamicMatrix<T>& mat) -> void;

template <typename T>
auto rank(DynamicMatrix<T> const& mat) -> typename DynamicMatrix<T>::size_type;

/// IMPLEMENTATON
///////////////////////////////////////////////////////////////////////////
template <typename T>
DynamicMatrix<T>::DynamicMatrix(size_type row, size_type col)
{
    resize(row, col);
}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(DynamicMatrix<T> const& other)
{
    (*this) = other;
}

template <typename T>
auto DynamicMatrix<T>::operator=(DynamicMatrix<T> const& other)
    -> DynamicMatrix<T>&
{
    resize(other.rows(), other.cols());
    auto const* ptr = other.data_.get();
    std::copy(ptr, std::next(ptr, size()), data_.get());
    return *this;
}

template <typename T>
auto DynamicMatrix<T>::size() const noexcept -> size_type
{
    return numRows_ * numCols_;
}

template <typename T>
auto DynamicMatrix<T>::empty() const noexcept -> bool
{
    return size() == size_type {};
}

template <typename T>
auto DynamicMatrix<T>::rows() const noexcept -> size_type
{
    return numRows_;
}

template <typename T>
auto DynamicMatrix<T>::cols() const noexcept -> size_type
{
    return numCols_;
}

template <typename T>
auto DynamicMatrix<T>::resize(size_type row, size_type col) -> void
{
    numRows_ = row;
    numCols_ = col;
    data_    = std::make_unique<value_type[]>(size()); // NOLINT
    clear();
}

template <typename T>
auto DynamicMatrix<T>::clear() noexcept -> void
{
    std::fill(data_.get(), std::next(data_.get(), size()), value_type {});
}

template <typename T>
auto DynamicMatrix<T>::at(size_type row, size_type col) -> value_type&
{
    if (row >= rows()) { throw std::out_of_range("row index out of bounds"); }
    if (col >= cols()) {
        throw std::out_of_range("column index out of bounds");
    }

    return data_[detail::matrixSubscriptToIndex(row, col, numCols_)];
}

template <typename T>
auto DynamicMatrix<T>::at(size_type row, size_type col) const
    -> value_type const&
{
    if (row >= rows()) { throw std::out_of_range("row index out of bounds"); }
    if (col >= cols()) {
        throw std::out_of_range("column index out of bounds");
    }

    return data_[detail::matrixSubscriptToIndex(row, col, numCols_)];
}

template <typename T>
auto DynamicMatrix<T>::operator()(size_type row, size_type col) -> value_type&
{
    return data_[detail::matrixSubscriptToIndex(row, col, numCols_)];
}

template <typename T>
auto DynamicMatrix<T>::operator()(size_type row, size_type col) const
    -> value_type const&
{
    return data_[detail::matrixSubscriptToIndex(row, col, numCols_)];
}

template <typename T>
auto operator==(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool
{
    return detail::matrixEqual(l, r);
}

template <typename T>
auto operator!=(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool
{
    return detail::matrixNotEqual(l, r);
}

template <typename T>
auto operator+(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
    -> DynamicMatrix<T>
{
    return detail::matrixAdd(l, r);
}

template <typename T>
auto operator+(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>
{
    return detail::matrixAdd(m, scaler);
}

template <typename T>
auto operator+(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>
{
    return detail::matrixAdd(m, scaler);
}

template <typename T>
auto operator-(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
    -> DynamicMatrix<T>
{
    return detail::matrixSubtract(l, r);
}

template <typename T>
auto operator-(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>
{
    return detail::matrixSubtract(m, scaler);
}

template <typename T>
auto operator-(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>
{
    return detail::matrixSubtract(m, scaler);
}

template <typename T>
auto operator*(DynamicMatrix<T> const& m, T scaler) -> DynamicMatrix<T>
{
    return detail::matrixMultiply(m, scaler);
}

template <typename T>
auto operator*(T scaler, DynamicMatrix<T> const& m) -> DynamicMatrix<T>
{
    return detail::matrixMultiply(m, scaler);
}

template <typename T>
auto operator*(DynamicMatrix<T> const& mat, DynamicVector<T> const& vec)
    -> DynamicVector<T>
{
    return detail::matrixMultiplyWithVector(mat, vec);
}

template <typename T>
auto operator<<(std::ostream& out, DynamicMatrix<T> const& m) -> std::ostream&
{
    return detail::matrixOutStream(out, m);
}

template <typename T>
auto subDynamicMatrix(DynamicMatrix<T> const& mat,
    typename DynamicMatrix<T>::size_type rowIdx,
    typename DynamicMatrix<T>::size_type colIdx) -> DynamicMatrix<T>
{
    auto result = DynamicMatrix<T> { mat.rows() - 1, mat.cols() - 1 };
    for (decltype(mat.rows()) row = 0; row < mat.rows(); ++row) {
        for (decltype(mat.rows()) col = 0; col < mat.cols(); ++col) {
            if ((row != rowIdx) && (col != colIdx)) {
                auto newRow            = row < rowIdx ? row : row - 1;
                auto newCol            = col < colIdx ? col : col - 1;
                result(newRow, newCol) = mat(row, col);
            }
        }
    }
    return result;
}

template <typename T>
auto determinant(DynamicMatrix<T> const& mat) ->
    typename DynamicMatrix<T>::value_type
{
    using value_type = typename DynamicMatrix<T>::value_type;

    if (!isSquare(mat)) {
        throw std::invalid_argument("matrix must be square");
    }

    if (mat.rows() == 2) {
        return (mat(0, 0) * mat(1, 1)) - (mat(0, 1) * mat(1, 0));
    }

    auto sum  = value_type { 0 };
    auto sign = value_type { 1 };
    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        auto sub = subDynamicMatrix(mat, 0, col);
        auto d   = determinant(sub);
        sum += mat(0, col) * d * sign;
        sign = -sign;
    }

    return sum;
}

template <typename T>
auto rowEchelon(DynamicMatrix<T>& mat) -> void
{
    if (mat.cols() < mat.rows()) {
        throw std::invalid_argument(
            "matrix must have at least have as many columns as rows");
    }

    using size_type                    = typename DynamicMatrix<T>::size_type;
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

template <typename T>
auto rank(DynamicMatrix<T> const& mat) -> typename DynamicMatrix<T>::size_type
{
    using size_type = typename DynamicMatrix<T>::size_type;

    auto copy = DynamicMatrix<T> { mat };
    rowEchelon(copy);

    auto numNonZeroRows = size_type {};
    if (!isRowEchelon(copy)) {
        auto subMatricies = std::vector<DynamicMatrix<T>> {};
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
                                auto sub = subDynamicMatrix(cur, i, j);
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