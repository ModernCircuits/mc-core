// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/_exception/uncaught_exceptions.hpp>

#include <utility>

#include <type_traits>

namespace mc::detail {

struct UncaughtExceptionCounter
{
    UncaughtExceptionCounter() = default;

    [[nodiscard]] auto newUncaughtException() const noexcept -> bool
    {
        return uncaught_exceptions() > _exceptionCount;
    }

private:
    decltype(uncaught_exceptions()) _exceptionCount{uncaught_exceptions()};
};

template<typename FunctionT, bool ExecuteOnException>
struct ScopeFail
{
    explicit ScopeFail(FunctionT const& fn) : _func{fn} {}

    explicit ScopeFail(FunctionT&& fn) : _func{std::move(fn)} {}

    ~ScopeFail() noexcept(ExecuteOnException)
    {
        if (ExecuteOnException == _ec.newUncaughtException() && _active) {
            _func();
        }
    }

    auto release() -> void { _active = false; }

private:
    FunctionT _func;
    UncaughtExceptionCounter _ec{};
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

}  // namespace mc::detail

#define SCOPE_FAIL                                                             \
    auto MC_ANONYMOUS_VAR(SCOPE_FAIL_STATE)                                    \
        = ::mc::detail::ScopeFailFactory{} + [&]()  // NOLINT
