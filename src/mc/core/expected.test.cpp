// SPDX-License-Identifier: BSL-1.0

#include <mc/core/expected.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace mc;

static auto example(int i) -> Expected<int, char const*>
{
    if (i < 5) {
        return 0;
    } else {
        return makeUnexpected("Error");
    }
}

TEST_CASE("expected.hpp: example", "[expected]")
{
    REQUIRE(example(0).has_value());
    REQUIRE_FALSE(example(42).has_value());
}
