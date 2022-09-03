// SPDX-License-Identifier: BSL-1.0

#include <mc/core/cmath.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("cmath.hpp: pow", "[cmath]", float, double)
{
    using T = TestType;

    REQUIRE(mc::pow(T(1), T(1)) == T(1));
    REQUIRE(mc::pow(T(2), T(2)) == T(4));
    STATIC_REQUIRE(mc::pow(T(1), T(1)) == T(1));
}
