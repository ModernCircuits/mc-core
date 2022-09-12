// SPDX-License-Identifier: BSL-1.0

#include <mc/core/array.hpp>
#include <mc/core/ranges.hpp>
#include <mc/core/vector.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ranges.hpp: example", "[ranges]")
{
    using namespace mc;

    auto v = Vector<int>{6, 2, 3, 4, 5, 6};
    REQUIRE(ranges::count(v, 6) == 2);

    auto a = Array<int, 6>{6, 2, 3, 4, 5, 6};
    REQUIRE(ranges::count(a, 6) == 2);
}
