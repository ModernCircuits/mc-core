#include "mc/numbers.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("stl/numbers: constants", "[stl][numbers]")
{
    REQUIRE(mc::numbers::e == Catch::Approx(2.7182818284590452353));
    REQUIRE(mc::numbers::log2e == Catch::Approx(1.4426950408889634073));
    REQUIRE(mc::numbers::log10e == Catch::Approx(0.4342944819032518276));
    REQUIRE(mc::numbers::pi == Catch::Approx(3.1415926535897932384));
    REQUIRE(mc::numbers::inv_pi == Catch::Approx(0.3183098861837906715));
    REQUIRE(mc::numbers::inv_sqrtpi == Catch::Approx(0.5641895835477562869));
    REQUIRE(mc::numbers::ln2 == Catch::Approx(0.6931471805599453094));
    REQUIRE(mc::numbers::ln10 == Catch::Approx(2.3025850929940456840));
    REQUIRE(mc::numbers::sqrt2 == Catch::Approx(1.4142135623730950488));
    REQUIRE(mc::numbers::sqrt3 == Catch::Approx(1.7320508075688772935));
    REQUIRE(mc::numbers::inv_sqrt3 == Catch::Approx(0.5773502691896257645));
    REQUIRE(mc::numbers::egamma == Catch::Approx(0.5772156649015328606));
    REQUIRE(mc::numbers::phi == Catch::Approx(1.6180339887498948482));
}
