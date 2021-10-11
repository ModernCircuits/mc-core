#include "mc/math.hpp"

#include <catch2/catch.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: normalized", "[math][algorithm]", float,
    double, long double)
{
    using T = TestType;

    auto lhs = math::DynamicVector<T> { 3 };

    lhs[0] = T { 4 };
    lhs[1] = T { 0 };
    lhs[2] = T { 0 };

    auto normalized = math::normalized(lhs);
    REQUIRE(normalized[0] == T { 2 });
    REQUIRE(normalized[1] == T { 0 });
    REQUIRE(normalized[2] == T { 0 });
}