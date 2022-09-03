// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/mutex.hpp>
#include <mc/core/optional.hpp>

#include <queue>

namespace mc {
template<typename T>
struct ThreadSafeQueue
{

    using value_type = T;
    using size_type  = typename std::queue<T>::size_type;

    ThreadSafeQueue()  = default;
    ~ThreadSafeQueue() = default;

    ThreadSafeQueue(ThreadSafeQueue const&)                    = delete;
    auto operator=(ThreadSafeQueue const&) -> ThreadSafeQueue& = delete;

    ThreadSafeQueue(ThreadSafeQueue&& other)              = delete;
    auto operator=(ThreadSafeQueue&&) -> ThreadSafeQueue& = delete;

    MC_NODISCARD auto pop() -> Optional<value_type>
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        if (_queue.empty()) { return Optional<value_type>{nullopt}; }
        value_type tmp = _queue.front();
        _queue.pop();
        return tmp;
    }

    auto push(value_type const& item) -> void
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        _queue.push(item);
    }

    auto push(value_type&& item) -> void
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        _queue.push(std::move(item));
    }

    MC_NODISCARD auto size() const -> size_type
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        return _queue.size();
    }

private:
    // Moved out of public interface to prevent races between this and pop().
    MC_NODISCARD auto empty() const -> bool { return _queue.empty(); }

    std::queue<value_type> _queue{};
    std::mutex mutable _mutex{};
};
}  // namespace mc
