// SPDX-License-Identifier: BSL-1.0

#include <mc/core/format.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/format: format", "[core][format]")
{
    REQUIRE(mc::format("{0}", 42) == "42");
}
