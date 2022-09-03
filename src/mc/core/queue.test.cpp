// SPDX-License-Identifier: BSL-1.0

#include <mc/core/queue.hpp>
#include <mc/core/thread.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("queue.hpp: ThreadSafeQueue", "[queue]", int, std::string)
{
    SECTION("single thread")
    {
        mc::ThreadSafeQueue<TestType> queue{};
        REQUIRE(queue.size() == 0);
        REQUIRE_FALSE(queue.pop().has_value());

        queue.push(TestType{});
        REQUIRE(queue.size() == 1);

        auto val = queue.pop();
        REQUIRE(queue.size() == 0);
        REQUIRE(val.has_value());
        REQUIRE(val.value() == TestType{});

        queue.push(TestType{});
        queue.push(TestType{});
        REQUIRE(queue.size() == 2);
    }

#if not defined(MC_EMSCRIPTEN)
    SECTION("two thread")
    {
        mc::ThreadSafeQueue<TestType> queue{};
        auto iterations = 10'000;
        auto thread     = std::thread([&queue, iterations] {
            for (auto i = 0; i < iterations; ++i) { queue.push(TestType{}); }
        });

        auto counter = 0;
        while (counter != iterations) {
            auto val = queue.pop();
            if (val.has_value()) {
                counter += 1;
                REQUIRE(val.value() == TestType{});
            }
        }

        thread.join();
    }
#endif
}
