// SPDX-License-Identifier: BSL-1.0

#include <mc/core/units.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("units.hpp: toMilliseconds", "[units]", int, long)
{
    using T            = TestType;
    using Seconds      = mc::Seconds<T>;
    using Milliseconds = mc::Milliseconds<T>;

    REQUIRE(mc::toMilliseconds(Seconds{1}).count() == T(1'000));
    REQUIRE(mc::toMilliseconds(Seconds{2}).count() == T(2'000));
    REQUIRE(mc::toMilliseconds(Milliseconds{2}).count() == T(2));
}

TEMPLATE_TEST_CASE("units.hpp: toSeconds", "[units]", int, long)
{
    using T            = TestType;
    using Seconds      = mc::Seconds<T>;
    using Milliseconds = mc::Milliseconds<T>;

    REQUIRE(mc::toSeconds(Seconds{1}).count() == T(1));
    REQUIRE(mc::toSeconds(Milliseconds{1'000}).count() == T(1));
}
