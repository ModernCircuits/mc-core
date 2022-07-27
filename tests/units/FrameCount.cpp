#include "mc/core/units/FrameCount.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stl/units: FrameCount", "[stl][units]")
{
    // .count()
    REQUIRE(mc::FrameCount().count() == 0ULL);
    REQUIRE(mc::FrameCount(0).count() == 0ULL);
    REQUIRE(mc::FrameCount(1).count() == 1ULL);

    // implicit conversion
    REQUIRE(mc::FrameCount(0) == 0ULL);

    // operations
    auto fc = mc::FrameCount { 0 };
    fc += 1ULL;
    REQUIRE(fc == 1ULL);
    fc += 2;
    REQUIRE(fc == 3ULL);
    fc += 4.0F;
    REQUIRE(fc == 7ULL);
    fc += 8.0;
    REQUIRE(fc == 15ULL);
}
