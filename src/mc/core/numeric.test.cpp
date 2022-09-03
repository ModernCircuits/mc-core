// SPDX-License-Identifier: BSL-1.0

#include <mc/core/numeric.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("numeric.hpp: lcm", "[numeric]", uint8_t, uint32_t, uint64_t)
{
    using T = TestType;
    REQUIRE(mc::lcm(T(0), T(0)) == T(0));
    REQUIRE(mc::lcm(T(1), T(0)) == T(0));
    REQUIRE(mc::lcm(T(0), T(1)) == T(0));
    REQUIRE(mc::lcm(T(2), T(1)) == T(2));
    REQUIRE(mc::lcm(T(4), T(1)) == T(4));
    REQUIRE(mc::lcm(T(4), T(3)) == T(12));
    REQUIRE(mc::lcm(T(10), T(2)) == T(10));
    REQUIRE(mc::lcm(T(11), T(3)) == T(33));
}

TEMPLATE_TEST_CASE("numeric.hpp: gcd", "[numeric]", uint8_t, uint32_t, uint64_t)
{
    using T = TestType;
    REQUIRE(mc::gcd(T(0), T(0)) == T(0));
    REQUIRE(mc::gcd(T(1), T(0)) == T(1));
    REQUIRE(mc::gcd(T(0), T(1)) == T(1));
    REQUIRE(mc::gcd(T(4), T(2)) == T(2));
}
