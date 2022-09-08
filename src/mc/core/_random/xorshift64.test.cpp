#include <mc/core/random.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace mc;

TEST_CASE("random.hpp: XorShift64", "[random]")  // NOLINT
{
    STATIC_REQUIRE(XorShift64::min() == 0);
    STATIC_REQUIRE(
        XorShift64::max() == std::numeric_limits<uint64_t>::max() - 1U
    );

    SECTION("default")
    {
        auto rng = XorShift64{};
        REQUIRE(rng() == 45454805674UL);
        REQUIRE(rng() == 11532217803599905471UL);
        REQUIRE(rng() == 10021416941527320954UL);

        rng.seed(XorShift64::default_seed);
        REQUIRE(rng() == 45454805674UL);
        REQUIRE(rng() == 11532217803599905471UL);
        REQUIRE(rng() == 10021416941527320954UL);
    }

    SECTION("seed = 1")
    {
        auto rng = XorShift64{1UL};
        CHECK(rng() == 1082269761UL);
        CHECK(rng() == 1152992998833853505UL);
        CHECK(rng() == 11177516664432764457UL);

        rng.seed(1UL);
        CHECK(rng() == 1082269761UL);
        CHECK(rng() == 1152992998833853505UL);
        CHECK(rng() == 11177516664432764457UL);

        rng.seed(1UL);
        rng.discard(2ULL);
        CHECK(rng() == 11177516664432764457UL);
    }
}
