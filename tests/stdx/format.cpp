#include "mc/format.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stl/format: format", "[stl][format]") { REQUIRE(mc::format("{0}", 42) == "42"); }
