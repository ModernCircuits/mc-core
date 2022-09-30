// SPDX-License-Identifier: BSL-1.0

#include <mc/core/utility.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace mc;

TEST_CASE("utility.hpp: integer_comparison_functions", "[utility]")  // NOLINT
{
    using namespace mc;

    STATIC_REQUIRE(sizeof(int) == 4);  // precondition

    // Quite surprisingly
    // REQUIRE(-1 > 1U);  //< warning: sign-unsign comparison
    // because after implicit conversion of -1 to the RHS type (`unsigned int`)
    // the expression is equivalent to:

    REQUIRE(0xFFFFFFFFU > 1U);
    REQUIRE(0xFFFFFFFFU == static_cast<unsigned>(-1));

    // In contrast, the cmp_* family compares integers as most expected -
    // negative signed integers always compare less than unsigned integers:
    REQUIRE(cmp_less(-1, 1U));
    REQUIRE(cmp_less_equal(-1, 1U));
    REQUIRE_FALSE(cmp_greater(-1, 1U));
    REQUIRE_FALSE(cmp_greater_equal(-1, 1U));

    REQUIRE(cmp_less(-99, 1U));
    REQUIRE(cmp_less_equal(-99, 1U));
    REQUIRE_FALSE(cmp_greater(-99, 1U));
    REQUIRE_FALSE(cmp_greater_equal(-99, 1U));

    REQUIRE(cmp_greater(1U, -1));
    REQUIRE(cmp_greater_equal(1U, -1));
    REQUIRE_FALSE(cmp_less(1U, -1));
    REQUIRE_FALSE(cmp_less_equal(1U, -1));

    // REQUIRE(-1 == 0xFFFFFFFFU);  //< warning: sign-unsign comparison
    REQUIRE(cmp_not_equal(-1, 0xFFFFFFFFU));
}
