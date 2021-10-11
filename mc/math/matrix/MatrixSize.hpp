#pragma once

#include "mc/config.hpp"
#include "mc/cstddef.hpp"

namespace mc {
namespace math {

struct MatrixSize {
    constexpr MatrixSize() noexcept = default;
    constexpr MatrixSize(std::size_t rows, std::size_t cols) noexcept
        : rows_ { rows }, cols_ { cols }
    {
    }

    MC_NODISCARD constexpr auto rows() const noexcept -> std::size_t
    {
        return rows_;
    }
    MC_NODISCARD constexpr auto columns() const noexcept -> std::size_t
    {
        return cols_;
    }

private:
    std::size_t rows_ { 0U };
    std::size_t cols_ { 0U };
};

MC_NODISCARD constexpr auto operator==(
    MatrixSize const& lhs, MatrixSize const& rhs) noexcept -> bool
{
    return (lhs.rows() == rhs.rows()) && (lhs.columns() == rhs.columns());
}

MC_NODISCARD constexpr auto operator!=(
    MatrixSize const& lhs, MatrixSize const& rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace math
} // namespace mc