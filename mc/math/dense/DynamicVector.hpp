#pragma once

#include "mc/math/iterator/begin.hpp"
#include "mc/math/iterator/data.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/end.hpp"
#include "mc/math/iterator/size.hpp"
#include "mc/math/traits/IsVector.hpp"
#include "mc/math/vector/operators.hpp"

#include "mc/algorithm.hpp"
#include "mc/cstddef.hpp"
#include "mc/numeric.hpp"
#include "mc/stdexcept.hpp"
#include "mc/vector.hpp"

namespace mc {
namespace math {

template <typename T>
struct DynamicVector {
    using value_type = T;
    using size_type  = std::size_t;

    DynamicVector() noexcept = default;
    explicit DynamicVector(size_type size);

    MC_NODISCARD auto data() noexcept -> T*;
    MC_NODISCARD auto data() const noexcept -> T const*;

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
    std::vector<T> data_ {};
};

// IMPLEMENTATION
template <typename T>
DynamicVector<T>::DynamicVector(size_type size)
{
    resize(size);
}

template <typename T>
auto DynamicVector<T>::data() noexcept -> T*
{
    return mc::data(data_);
}

template <typename T>
auto DynamicVector<T>::data() const noexcept -> T const*
{
    return mc::data(data_);
}

template <typename T>
auto DynamicVector<T>::begin() noexcept -> T*
{
    return data();
}

template <typename T>
auto DynamicVector<T>::begin() const noexcept -> T const*
{
    return data();
}

template <typename T>
auto DynamicVector<T>::cbegin() const noexcept -> T const*
{
    return data();
}

template <typename T>
auto DynamicVector<T>::end() noexcept -> T*
{
    return data() + size();
}

template <typename T>
auto DynamicVector<T>::end() const noexcept -> T const*
{
    return data() + size();
}

template <typename T>
auto DynamicVector<T>::cend() const noexcept -> T const*
{
    return data() + size();
}

template <typename T>
auto DynamicVector<T>::clear() noexcept -> void
{
    std::fill(begin(), end(), T {});
}

template <typename T>
auto DynamicVector<T>::resize(size_type size) -> void
{
    data_.resize(size);
    clear();
}

template <typename T>
auto DynamicVector<T>::size() const noexcept -> size_type
{
    return mc::size(data_);
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