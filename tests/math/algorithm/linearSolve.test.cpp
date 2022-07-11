#include "mc/math.hpp"

#include <catch2/catch_template_test_macros.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: linearSolve", "[math][algorithm]", float, double, long double)
{
    using T = TestType;

    auto a  = math::DynamicMatrix<T> { 3, 3 };
    a(0, 0) = T { 1 };
    a(0, 1) = T { 3 };
    a(0, 2) = T { -1 };
    a(1, 0) = T { 4 };
    a(1, 1) = T { -1 };
    a(1, 2) = T { 1 };
    a(2, 0) = T { 2 };
    a(2, 1) = T { 4 };
    a(2, 2) = T { 3 };

    auto b = math::DynamicVector<T> { 3 };
    b[0]   = T { 13 };
    b[1]   = T { 9 };
    b[2]   = T { -6 };

    auto result = math::linearSolve(a, b);
    REQUIRE(result.vec.size() == 3);
    REQUIRE(result.success == math::LinearSolveSolution::Unique);
    REQUIRE(math::approx(result.vec[0], T { 4 }));
    REQUIRE(math::approx(result.vec[1], T { 1 }));
    REQUIRE(math::approx(result.vec[2], T { -6 }));

    a.clear();
    b.clear();
    a(0, 0) = T { 1 };
    a(0, 1) = T { 0 };
    a(0, 2) = T { 0 };
    a(1, 0) = T { 0 };
    a(1, 1) = T { 1 };
    a(1, 2) = T { 0 };
    a(2, 0) = T { 1 };
    a(2, 1) = T { 1 };
    a(2, 2) = T { 0 };
    result  = math::linearSolve(a, b);
    REQUIRE(result.success == math::LinearSolveSolution::NoUnique);

    a.clear();
    b.clear();
    a(0, 0) = T { 1 };
    a(0, 1) = T { 0 };
    a(0, 2) = T { 0 };
    a(1, 0) = T { 1 };
    a(1, 1) = T { 0 };
    a(1, 2) = T { 0 };
    a(2, 0) = T { 1 };
    a(2, 1) = T { 0 };
    a(2, 2) = T { 0 };
    b[0]    = T { 0 };
    b[1]    = T { -1 };
    b[2]    = T { 1 };
    result  = math::linearSolve(a, b);
    REQUIRE(result.success == math::LinearSolveSolution::None);
}