#include "mc/math.hpp"

#include <catch2/catch.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: normalize", "[math][algorithm]", float, double, long double)
{
    using T = TestType;

    auto lhs = math::DynamicVector<T> { 3 };
    lhs[0]   = T { 4 };
    lhs[1]   = T { 0 };
    lhs[2]   = T { 0 };

    math::normalize(lhs);
    REQUIRE(lhs[0] == T { 2 });
    REQUIRE(lhs[1] == T { 0 });
    REQUIRE(lhs[2] == T { 0 });
}