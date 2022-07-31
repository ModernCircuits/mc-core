// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/stdx/exception_N4152.hpp>

#include <utility>

#include <type_traits>

namespace mc {

namespace detail {

struct UncaughtExceptionCounter
{
    UncaughtExceptionCounter() = default;

    [[nodiscard]] auto newUncaughtException() const noexcept -> bool
    {
        return uncaught_exceptions() > exceptionCount_;
    }

private:
    decltype(uncaught_exceptions()) exceptionCount_{uncaught_exceptions()};
};

template<typename FunctionT, bool ExecuteOnException>
struct ScopeFail
{
    explicit ScopeFail(FunctionT const& fn) : func_{fn} {}

    explicit ScopeFail(FunctionT&& fn) : func_{std::move(fn)} {}

    ~ScopeFail() noexcept(ExecuteOnException)
    {
        if (ExecuteOnException == ec_.newUncaughtException() && _active) {
            func_();
        }
    }

    auto release() -> void { _active = false; }

private:
    FunctionT func_;
    UncaughtExceptionCounter ec_{};
    bool _active{true};
};

enum struct ScopeFailFactory
{};

template<typename FuncT>
auto operator+(ScopeFailFactory /*tag*/, FuncT&& fn)
    -> ScopeFail<std::decay_t<FuncT>, true>
{
    return ScopeFail<std::decay_t<FuncT>, true>(static_cast<FuncT&&>(fn));
}

}  // namespace detail

}  // namespace mc

#define SCOPE_FAIL                                                             \
    auto MC_ANONYMOUS_VARIABLE(SCOPE_FAIL_STATE)                               \
        = ::mc::detail::ScopeFailFactory{} + [&]()  // NOLINT
