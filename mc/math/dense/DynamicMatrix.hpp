#pragma once

#include "mc/algorithm.hpp"
#include "mc/config.hpp"
#include "mc/cstddef.hpp"
#include "mc/cstdint.hpp"
#include "mc/iterator.hpp"
#include "mc/math/iterator/data.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/size.hpp"
#include "mc/math/matrix/detail/matrixSubscriptToIndex.hpp"
#include "mc/math/matrix/determinant.hpp"
#include "mc/math/matrix/findRowWithMaxElement.hpp"
#include "mc/math/matrix/inverse.hpp"
#include "mc/math/matrix/isNonZero.hpp"
#include "mc/math/matrix/isRowEchelon.hpp"
#include "mc/math/matrix/isSquare.hpp"
#include "mc/math/matrix/join.hpp"
#include "mc/math/matrix/makeIdentity.hpp"
#include "mc/math/matrix/multiplyAddRow.hpp"
#include "mc/math/matrix/multiplyRow.hpp"
#include "mc/math/matrix/operators.hpp"
#include "mc/math/matrix/rank.hpp"
#include "mc/math/matrix/rowEchelon.hpp"
#include "mc/math/matrix/splitColumns.hpp"
#include "mc/math/matrix/subMatrix.hpp"
#include "mc/math/matrix/swapRow.hpp"
#include "mc/math/traits/IsDenseMatrix.hpp"
#include "mc/memory.hpp"

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

    MC_NODISCARD auto data() -> T*;
    MC_NODISCARD auto data() const -> T const*;

private:
    std::unique_ptr<T[]> data_ { nullptr }; // NOLINT
    size_type numRows_ {};
    size_type numCols_ {};
};

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
auto DynamicMatrix<T>::data() -> T*
{
    return data_.get();
}

template <typename T>
auto DynamicMatrix<T>::data() const -> T const*
{
    return data_.get();
}

template <typename T>
struct IsDenseMatrix<DynamicMatrix<T>> : TrueType {
};
} // namespace math
} // namespace mc