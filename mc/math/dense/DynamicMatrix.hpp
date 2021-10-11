#pragma once

#include "mc/math/algorithm/linearSolve.hpp"
#include "mc/math/dense/DynamicVector.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/size.hpp"

#include "mc/math/matrix/detail/matrixAdd.hpp"
#include "mc/math/matrix/detail/matrixCompare.hpp"
#include "mc/math/matrix/detail/matrixMultiply.hpp"
#include "mc/math/matrix/detail/matrixStream.hpp"
#include "mc/math/matrix/detail/matrixSubscriptToIndex.hpp"
#include "mc/math/matrix/detail/matrixSubtract.hpp"

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
auto compareEqual(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool;

template <typename T>
auto isSquare(DynamicMatrix<T> const& mat) -> bool;

template <typename T>
auto swapRow(DynamicMatrix<T>& mat, typename DynamicMatrix<T>::size_type a,
    typename DynamicMatrix<T>::size_type b) -> void;

template <typename T>
auto multiplyRow(DynamicMatrix<T>& mat,
    typename DynamicMatrix<T>::size_type row, T factor) -> void;

template <typename T>
auto multiplyAddRow(DynamicMatrix<T>& mat,
    typename DynamicMatrix<T>::size_type source,
    typename DynamicMatrix<T>::size_type dest, T factor) -> void;

template <typename T>
auto findRowWithMaxElement(DynamicMatrix<T> const& mat,
    typename DynamicMatrix<T>::size_type col,
    typename DynamicMatrix<T>::size_type startRow) ->
    typename DynamicMatrix<T>::size_type;

template <typename T>
auto join(DynamicMatrix<T> const& a, DynamicMatrix<T> const& b)
    -> DynamicMatrix<T>;

template <typename T>
auto splitColumns(
    DynamicMatrix<T> const& mat, typename DynamicMatrix<T>::size_type colIdx)
    -> std::pair<DynamicMatrix<T>, DynamicMatrix<T>>;

template <typename T>
auto makeIdentity(typename DynamicMatrix<T>::size_type size)
    -> DynamicMatrix<T>;

template <typename T>
auto makeIdentity(DynamicMatrix<T>& mat) -> void;

template <typename T>
auto inverse(DynamicMatrix<T> const& mat) -> DynamicMatrix<T>;

template <typename T>
auto subDynamicMatrix(DynamicMatrix<T> const& mat,
    typename DynamicMatrix<T>::size_type rowIdx,
    typename DynamicMatrix<T>::size_type colIdx) -> DynamicMatrix<T>;

template <typename T>
auto determinant(DynamicMatrix<T> const& mat) ->
    typename DynamicMatrix<T>::value_type;

template <typename T>
auto isNonZero(DynamicMatrix<T> const& mat) -> bool;

template <typename T>
auto isRowEchelon(DynamicMatrix<T> const& mat) -> bool;

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

// template<typename T>
// auto operator*(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r)
//     -> DynamicMatrix<T>
// {
//     using size_type = typename DynamicMatrix<T>::size_type;
//     auto tmp        = DynamicMatrix<T> {l.rows(), l.cols()};
//     if (l.cols() == r.cols())
//     {
//         for (size_type lRow = 0; lRow < l.rows(); ++lRow)
//         {
//             for (size_type rCol = 0; rCol < r.cols(); ++rCol)
//             {
//                 auto result = T {};
//                 for (size_type lCol = 0; lCol < l.cols(); ++lCol)
//                 {
//                     auto const lIndex = (lRow * l.cols()) + lCol;
//                     auto const rIndex = (lCol * r.cols()) + rCol;
//                     result += l.data()[lIndex] + r.data()[rIndex];
//                 }

//                 auto const resultIndex  = (lRow + r.cols()) + rCol;
//                 tmp.data()[resultIndex] = result;
//             }
//         }
//     }
//     return tmp;
// }

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
auto isSquare(DynamicMatrix<T> const& mat) -> bool
{
    return mat.rows() == mat.cols();
}

template <typename T>
auto swapRow(DynamicMatrix<T>& mat, typename DynamicMatrix<T>::size_type a,
    typename DynamicMatrix<T>::size_type b) -> void
{
    if ((a >= mat.rows()) || (b >= mat.rows())) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        std::swap(mat(a, col), mat(b, col));
    }
}

template <typename T>
auto multiplyRow(DynamicMatrix<T>& mat,
    typename DynamicMatrix<T>::size_type row, T factor) -> void
{
    if (row >= mat.rows()) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        mat(row, col) *= factor;
    }
}

template <typename T>
auto multiplyAddRow(DynamicMatrix<T>& mat,
    typename DynamicMatrix<T>::size_type source,
    typename DynamicMatrix<T>::size_type dest, T factor) -> void
{
    if ((source >= mat.rows()) || (source >= mat.rows())) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        mat(dest, col) += mat(source, col) * factor;
    }
}

template <typename T>
auto findRowWithMaxElement(DynamicMatrix<T> const& mat,
    typename DynamicMatrix<T>::size_type col,
    typename DynamicMatrix<T>::size_type startRow) ->
    typename DynamicMatrix<T>::size_type
{
    using size_type = typename DynamicMatrix<T>::size_type;

    if (startRow >= mat.rows()) {
        throw std::out_of_range("row index out of bounds");
    }
    if (col >= mat.cols()) {
        throw std::out_of_range("column index out of bounds");
    }

    size_type maxId = startRow;
    for (size_type row = startRow; row < mat.rows(); ++row) {
        if (mat(row, col) >= mat(maxId, col)) { maxId = row; }
    }

    return maxId;
}

template <typename T>
auto join(DynamicMatrix<T> const& a, DynamicMatrix<T> const& b)
    -> DynamicMatrix<T>
{
    using size_type = typename DynamicMatrix<T>::size_type;

    if (a.rows() != b.rows()) {
        throw std::invalid_argument("rows size must match");
    }

    auto result = DynamicMatrix<T> { a.rows(), a.cols() + b.cols() };

    for (size_type row = 0; row < result.rows(); ++row) {
        for (size_type col = 0; col < result.cols(); ++col) {
            auto const& source   = col < a.cols() ? a : b;
            auto const sourceCol = col < a.cols() ? col : col - a.cols();
            result(row, col)     = source(row, sourceCol);
        }
    }

    return result;
}

template <typename T>
auto splitColumns(
    DynamicMatrix<T> const& mat, typename DynamicMatrix<T>::size_type colIdx)
    -> std::pair<DynamicMatrix<T>, DynamicMatrix<T>>
{
    using size_type = typename DynamicMatrix<T>::size_type;

    if (colIdx >= mat.cols()) {
        throw std::out_of_range("column index out of bounds");
    }

    auto const numRows = mat.rows();
    auto const numColA = colIdx;
    auto const numColB = mat.cols() - colIdx;

    auto a = DynamicMatrix<T> { numRows, numColA };
    auto b = DynamicMatrix<T> { numRows, numColB };

    for (size_type row = 0; row < numRows; ++row) {
        for (size_type col = 0; col < mat.cols(); ++col) {
            if (col < colIdx) {
                a(row, col) = mat(row, col);
            } else {
                b(row, col - colIdx) = mat(row, col);
            }
        }
    }

    return std::make_pair(a, b);
}

template <typename T>
auto makeIdentity(typename DynamicMatrix<T>::size_type size) -> DynamicMatrix<T>
{
    auto mat = DynamicMatrix<T> { size, size };
    makeIdentity(mat);
    return mat;
}

template <typename T>
auto makeIdentity(DynamicMatrix<T>& mat) -> void
{
    if (!isSquare(mat)) {
        throw std::invalid_argument("matrix must be square");
    }

    mat.clear();
    for (decltype(mat.rows()) i = 0; i < mat.rows(); ++i) {
        mat(i, i) = T { 1 };
    }
}

template <typename T>
auto inverse(DynamicMatrix<T> const& mat) -> DynamicMatrix<T>
{
    using size_type = typename DynamicMatrix<T>::size_type;

    if (!isSquare(mat)) {
        throw std::invalid_argument("matrix must be square");
    }

    static constexpr auto maxLoopCount = size_type { 100 };

    auto const identity = makeIdentity<T>(mat.rows());
    auto augment        = join(mat, identity);

    auto count     = size_type { 0 };
    auto completed = false;

    auto cRow = size_type {};
    auto cCol = size_type {};

    auto result = DynamicMatrix<T> { mat.rows(), mat.cols() };
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
        if (compareEqual(splits.first, identity)) {
            completed = true;
            result    = splits.second;
        }

        count += 1;
    }

    return result;
}

template <typename T>
auto compareEqual(DynamicMatrix<T> const& l, DynamicMatrix<T> const& r) -> bool
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
auto isNonZero(DynamicMatrix<T> const& mat) -> bool
{
    for (decltype(mat.rows()) row { 0 }; row < mat.rows(); ++row) {
        for (decltype(mat.cols()) col { 0 }; col < mat.cols(); ++col) {
            if (!approx(mat(row, col), T {})) { return true; }
        }
    }
    return false;
}

template <typename T>
auto isRowEchelon(DynamicMatrix<T> const& mat) -> bool
{
    auto sum = T {};
    for (decltype(mat.rows()) row { 1 }; row < mat.rows(); ++row) {
        for (decltype(mat.cols()) col { 0 }; col < row; ++col) {
            sum += mat(row, col);
        }
    }

    return approx(sum, T {});
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