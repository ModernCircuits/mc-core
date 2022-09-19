// SPDX-License-Identifier: BSL-1.0

#include <mc/core/mdspan.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("mdspan.hpp: example", "[mdspan]")
{
    double buffer[2 * 3 * 4] = {};  // NOLINT

    auto s1     = mc::mdspan<double, 2, 3, 4>(buffer);
    s1(1, 1, 1) = 42;

    auto sub1 = mc::subspan(s1, 1, 1, mc::all);
    REQUIRE(sub1[1] == 42);
}
