// SPDX-License-Identifier: BSL-1.0

#include <mc/core/bit.hpp>
#include <mc/core/cstdint.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("bit.hpp: byteswap", "[bit]", )
{
    using namespace mc;

    SECTION("8bit")
    {
        REQUIRE(byteswap('a') == 'a');
        REQUIRE(byteswap('b') == 'b');
    }

    SECTION("16bit")
    {
        REQUIRE(byteswap(uint16_t(0xAABB)) == uint16_t(0xBBAA));
        REQUIRE(byteswap(uint16_t(0xCAFE)) == uint16_t(0xFECA));
    }

    SECTION("32bit")
    {
        REQUIRE(byteswap(uint32_t(0xAABBCCDD)) == uint32_t(0xDDCCBBAA));
        REQUIRE(byteswap(uint32_t(0xCAFE0000)) == uint32_t(0x0000FECA));
    }
}
