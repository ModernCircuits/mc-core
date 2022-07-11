#include "mc/math.hpp"

#include "mc/cstring.hpp"

#include <catch2/catch_template_test_macros.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: dotProduct", "[math][algorithm]", float, double, long double)
{
    using T = TestType;

    auto lhs = math::DynamicVector<T> { 2 };
    auto rhs = math::DynamicVector<T> { 2 };
    lhs[0]   = T { 1 };
    lhs[1]   = T { 2 };
    rhs[0]   = T { 1 };
    rhs[1]   = T { 2 };
    REQUIRE(math::dotProduct(lhs, rhs) == T { 5 });

    rhs[0] = T { 4 };
    rhs[1] = T { 4 };
    REQUIRE(math::dotProduct(lhs, rhs) == T { 12 });

    lhs.resize(3);
    rhs.resize(3);
    lhs[0] = T { 1 };
    lhs[1] = T { 2 };
    lhs[2] = T { 3 };

    rhs[0] = T { 1 };
    rhs[1] = T { 2 };
    rhs[2] = T { 3 };

    try {
        math::dotProduct(lhs, math::DynamicVector<T> { 16 });
        REQUIRE(false);
    } catch (std::domain_error const& e) {
        auto const* msg = "vectors need to be the same size";
        REQUIRE((std::strcmp(e.what(), msg) == 0));
    }
}