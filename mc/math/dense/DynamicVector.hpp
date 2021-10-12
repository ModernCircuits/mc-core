#pragma once

#include "mc/math/iterator/begin.hpp"
#include "mc/math/iterator/data.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/end.hpp"
#include "mc/math/iterator/size.hpp"
#include "mc/math/traits/IsVector.hpp"
#include "mc/math/vector/operators.hpp"

#include "mc/algorithm.hpp"
#include "mc/cmath.hpp"
#include "mc/cstddef.hpp"
#include "mc/cstdint.hpp"
#include "mc/iterator.hpp"
#include "mc/memory.hpp"
#include "mc/numeric.hpp"
#include "mc/ostream.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {

template <typename T>
struct DynamicVector {
    using value_type = T;
    using size_type  = std::uint32_t;

    DynamicVector() noexcept = default;
    explicit DynamicVector(size_type size);
    DynamicVector(DynamicVector<T> const& other);

    auto operator=(DynamicVector<T> const& other) -> DynamicVector<T>&;

    MC_NODISCARD auto begin() noexcept -> T*;
    MC_NODISCARD auto begin() const noexcept -> T const*;
    MC_NODISCARD auto cbegin() const noexcept -> T const*;

    MC_NODISCARD auto end() noexcept -> T*;
    MC_NODISCARD auto end() const noexcept -> T const*;
    MC_NODISCARD auto cend() const noexcept -> T const*;

    MC_NODISCARD auto empty() const noexcept -> bool;
    MC_NODISCARD auto size() const noexcept -> size_type;

    auto clear() noexcept -> void;
    auto resize(size_type size) -> void;

    MC_NODISCARD auto at(size_type idx) -> T&;
    MC_NODISCARD auto at(size_type idx) const -> T const&;

    MC_NODISCARD auto operator[](size_type idx) -> T&;
    MC_NODISCARD auto operator[](size_type idx) const -> T const&;

private:
    std::unique_ptr<T[]> data_ {}; // NOLINT
    size_type size_ {};
};

// IMPLEMENTATION
template <typename T>
DynamicVector<T>::DynamicVector(size_type size)
{
    resize(size);
}

template <typename T>
DynamicVector<T>::DynamicVector(DynamicVector<T> const& other)
{
    (*this) = other;
}

template <typename T>
auto DynamicVector<T>::operator=(DynamicVector<T> const& other)
    -> DynamicVector<T>&
{
    resize(other.size());
    std::copy(other.cbegin(), other.cend(), begin());
    return *this;
}

template <typename T>
auto DynamicVector<T>::begin() noexcept -> T*
{
    return data_.get();
}

template <typename T>
auto DynamicVector<T>::begin() const noexcept -> T const*
{
    return data_.get();
}

template <typename T>
auto DynamicVector<T>::cbegin() const noexcept -> T const*
{
    return data_.get();
}

template <typename T>
auto DynamicVector<T>::end() noexcept -> T*
{
    return begin() + size();
}

template <typename T>
auto DynamicVector<T>::end() const noexcept -> T const*
{
    return begin() + size();
}

template <typename T>
auto DynamicVector<T>::cend() const noexcept -> T const*
{
    return begin() + size();
}

template <typename T>
auto DynamicVector<T>::clear() noexcept -> void
{
    std::fill(begin(), end(), T {});
}

template <typename T>
auto DynamicVector<T>::resize(size_type size) -> void
{
    size_ = size;
    data_ = std::make_unique<value_type[]>(this->size()); // NOLINT
    clear();
}

template <typename T>
auto DynamicVector<T>::size() const noexcept -> size_type
{
    return size_;
}

template <typename T>
auto DynamicVector<T>::empty() const noexcept -> bool
{
    return size() == size_type {};
}

template <typename T>
auto DynamicVector<T>::at(size_type idx) -> value_type&
{
    if (idx >= size()) { throw std::out_of_range("index out of bounds"); }
    return data_[idx];
}

template <typename T>
auto DynamicVector<T>::at(size_type idx) const -> value_type const&
{
    if (idx >= size()) { throw std::out_of_range("index out of bounds"); }
    return data_[idx];
}

template <typename T>
auto DynamicVector<T>::operator[](size_type idx) -> value_type&
{
    return data_[idx];
}

template <typename T>
auto DynamicVector<T>::operator[](size_type idx) const -> value_type const&
{
    return data_[idx];
}

template <typename T>
struct IsVector<DynamicVector<T>> : TrueType {
};
} // namespace math
} // namespace mc