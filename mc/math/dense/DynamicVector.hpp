#pragma once

#include "mc/math/iterator/begin.hpp"
#include "mc/math/iterator/data.hpp"
#include "mc/math/iterator/empty.hpp"
#include "mc/math/iterator/end.hpp"
#include "mc/math/iterator/size.hpp"

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

template <typename T>
auto operator==(DynamicVector<T> const& l, DynamicVector<T> const& r) -> bool;

template <typename T>
auto operator!=(DynamicVector<T> const& l, DynamicVector<T> const& r) -> bool;

template <typename T>
auto operator+(DynamicVector<T> const& l, DynamicVector<T> const& r)
    -> DynamicVector<T>;

template <typename T>
auto operator-(DynamicVector<T> const& l, DynamicVector<T> const& r)
    -> DynamicVector<T>;

template <typename T>
auto operator*(DynamicVector<T> const& vec, T const& scaler)
    -> DynamicVector<T>;

template <typename T>
auto operator*(T const& scaler, DynamicVector<T> const& vec)
    -> DynamicVector<T>;

template <typename T>
auto operator<<(std::ostream& out, DynamicVector<T> const& vec)
    -> std::ostream&;

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
auto operator==(DynamicVector<T> const& l, DynamicVector<T> const& r) -> bool
{
    return std::equal(begin(l), end(l), begin(r), end(r));
}

template <typename T>
auto operator!=(DynamicVector<T> const& l, DynamicVector<T> const& r) -> bool
{
    return !(l == r);
}

template <typename T>
auto operator+(DynamicVector<T> const& l, DynamicVector<T> const& r)
    -> DynamicVector<T>
{
    if (size(l) != size(r)) {
        throw std::domain_error("vectors need to be the same size");
    }
    auto result = DynamicVector<T> { size(l) };
    std::transform(
        cbegin(l), cend(l), cbegin(r), begin(result), std::plus<T> {});
    return result;
}

template <typename T>
auto operator-(DynamicVector<T> const& l, DynamicVector<T> const& r)
    -> DynamicVector<T>
{
    if (size(l) != size(r)) {
        throw std::domain_error("vectors need to be the same size");
    }
    auto result = DynamicVector<T> { size(l) };
    std::transform(
        cbegin(l), cend(l), cbegin(r), begin(result), std::minus<T> {});
    return result;
}

template <typename T>
auto operator*(DynamicVector<T> const& vec, T const& scaler) -> DynamicVector<T>
{
    auto result = DynamicVector<T> { size(vec) };
    std::transform(cbegin(vec), cend(vec), begin(result),
        [scaler](auto v) { return v * scaler; });
    return result;
}

template <typename T>
auto operator*(T const& scaler, DynamicVector<T> const& vec) -> DynamicVector<T>
{
    return vec * scaler;
}

template <typename T>
auto operator<<(std::ostream& out, DynamicVector<T> const& vec) -> std::ostream&
{
    for (decltype(size(vec)) i = 0; i < size(vec); ++i) {
        out << vec[i] << ' ';
    }
    return out;
}

} // namespace math
} // namespace mc