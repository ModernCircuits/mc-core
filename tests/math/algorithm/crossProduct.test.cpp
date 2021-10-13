#include "mc/math.hpp"

#include "mc/cstring.hpp"

#include <catch2/catch.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: crossProduct", "[math][algorithm]", float, double, long double)
{
    using T = TestType;

    auto lhs = math::DynamicVector<T> { 3 };
    auto rhs = math::DynamicVector<T> { 3 };
    lhs[0]   = T { 1 };
    lhs[1]   = T { 2 };
    lhs[2]   = T { 3 };

    rhs[0] = T { 1 };
    rhs[1] = T { 2 };
    rhs[2] = T { 3 };

    auto cross = math::crossProduct(lhs, rhs);
    REQUIRE(cross[0] == T { 0 });
    REQUIRE(cross[1] == T { 0 });
    REQUIRE(cross[2] == T { 0 });

    try {
        math::crossProduct(lhs, math::DynamicVector<T> { 16 });
        REQUIRE(false);
    } catch (std::domain_error const& e) {
        constexpr auto const* msg = "vectors need to be the same size";
        REQUIRE((std::strcmp(e.what(), msg) == 0));
    }

    try {
        math::crossProduct(math::DynamicVector<T> { 16 }, math::DynamicVector<T> { 16 });
        REQUIRE(false);
    } catch (std::domain_error const& e) {
        constexpr auto const* msg = "only 3-dimensional vector supported";
        REQUIRE((std::strcmp(e.what(), msg) == 0));
    }
}