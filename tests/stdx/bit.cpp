#include "mc/bit.hpp"

#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("stl/bit: bit_ceil", "[stl][bit]", unsigned char, unsigned short, unsigned int, unsigned long)
{
    using T = TestType;
    REQUIRE(mc::bit_ceil(T(1)) == T(1));
    REQUIRE(mc::bit_ceil(T(2)) == T(2));
    REQUIRE(mc::bit_ceil(T(3)) == T(4));
    REQUIRE(mc::bit_ceil(T(4)) == T(4));
    REQUIRE(mc::bit_ceil(T(15)) == T(16));
    REQUIRE(mc::bit_ceil(T(21)) == T(32));
    REQUIRE(mc::bit_ceil(T(33)) == T(64));
    REQUIRE(mc::bit_ceil(T(55)) == T(64));
}
