// SPDX-License-Identifier: BSL-1.0

#include <mc/core/random.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace mc;

TEST_CASE("random.hpp: XorShift32", "[random]")  // NOLINT
{
    STATIC_REQUIRE(XorShift32::min() == 0);
    STATIC_REQUIRE(
        XorShift32::max() == std::numeric_limits<uint32_t>::max() - 1U
    );

    SECTION("default")
    {
        auto rng = XorShift32{};
        REQUIRE(rng() == 11355432U);
        REQUIRE(rng() == 2836018348U);
        REQUIRE(rng() == 476557059U);

        rng.seed(XorShift32::default_seed);
        REQUIRE(rng() == 11355432U);
        REQUIRE(rng() == 2836018348U);
        REQUIRE(rng() == 476557059U);

        rng.seed(XorShift32::default_seed);
        rng.discard(2ULL);
        REQUIRE(rng() == 476557059U);
    }
}
