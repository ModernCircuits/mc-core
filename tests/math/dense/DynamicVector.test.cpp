#include "mc/math.hpp"

#include "mc/cstring.hpp"
#include "mc/sstream.hpp"
#include "mc/utility.hpp"

#include <catch2/catch.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/dense: DynamicVector", "[math][dense][vector]", float, double, long double)
{
    using T = TestType;

    auto vec = math::DynamicVector<T> { 2 };
    REQUIRE(vec.size() == 2);

    vec.resize(3);
    REQUIRE(vec.size() == 3);

    REQUIRE(vec.at(0) == T {});
    REQUIRE(vec.at(1) == T {});
    REQUIRE(vec.at(2) == T {});

    REQUIRE(vec[0] == T {});
    REQUIRE(vec[1] == T {});
    REQUIRE(vec[2] == T {});

    REQUIRE(vec == vec);
    REQUIRE(!(vec != vec));

    vec[0] = T { 1 };
    vec[1] = T { 2 };
    vec[2] = T { 3 };

    REQUIRE(vec[0] == T { 1 });
    REQUIRE(vec[1] == T { 2 });
    REQUIRE(vec[2] == T { 3 });

    auto otherSize = math::DynamicVector<T> {};
    REQUIRE(otherSize.size() == 0);
    REQUIRE(vec != otherSize);
    REQUIRE(!(vec == otherSize));

    auto sameSize = math::DynamicVector<T> { 3 };
    REQUIRE(vec != sameSize);
    REQUIRE(!(vec == sameSize));

    vec.clear();
    REQUIRE(vec == sameSize);
    REQUIRE(!(vec != sameSize));

    auto const zeroAdd = vec + sameSize;
    REQUIRE(zeroAdd.size() == 3);
    REQUIRE(zeroAdd[0] == T {});
    REQUIRE(zeroAdd[1] == T {});
    REQUIRE(zeroAdd[2] == T {});

    auto const zeroSub = vec - sameSize;
    REQUIRE(zeroSub.size() == 3);
    REQUIRE(zeroSub.at(0) == T {});
    REQUIRE(zeroSub.at(1) == T {});
    REQUIRE(zeroSub.at(2) == T {});

    vec[0] = T { 1 };
    vec[1] = T { 2 };
    vec[2] = T { 3 };

    auto halfZeroAdd = vec + sameSize;
    REQUIRE(halfZeroAdd.size() == 3);
    REQUIRE(halfZeroAdd[0] == T { 1 });
    REQUIRE(halfZeroAdd[1] == T { 2 });
    REQUIRE(halfZeroAdd[2] == T { 3 });

    auto halfZeroSub = vec - sameSize;
    REQUIRE(halfZeroSub.size() == 3);
    REQUIRE(halfZeroSub[0] == T { 1 });
    REQUIRE(halfZeroSub[1] == T { 2 });
    REQUIRE(halfZeroSub[2] == T { 3 });

    sameSize[0] = T { 1 };
    sameSize[1] = T { 1 };
    sameSize[2] = T { 1 };

    auto add = vec + sameSize;
    REQUIRE(add.size() == 3);
    REQUIRE(add[0] == T { 2 });
    REQUIRE(add[1] == T { 3 });
    REQUIRE(add[2] == T { 4 });

    auto sub = vec - sameSize;
    REQUIRE(sub.size() == 3);
    REQUIRE(sub[0] == T { 0 });
    REQUIRE(sub[1] == T { 1 });
    REQUIRE(sub[2] == T { 2 });

    auto scaled2 = vec * T { 2 };
    REQUIRE(scaled2.size() == 3);
    REQUIRE(scaled2[0] == T { 2 });
    REQUIRE(scaled2[1] == T { 4 });
    REQUIRE(scaled2[2] == T { 6 });

    auto scaled4 = T { 4 } * vec;
    REQUIRE(scaled4.size() == 3);
    REQUIRE(scaled4[0] == T { 4 });
    REQUIRE(scaled4[1] == T { 8 });
    REQUIRE(scaled4[2] == T { 12 });

    try {
        auto fail = vec + math::DynamicVector<T> { 5 };
        REQUIRE(false);
    } catch (std::domain_error const& e) {
        auto const* msg = "vectors need to be the same size";
        REQUIRE((std::strcmp(e.what(), msg) == 0));
    }

    try {
        auto fail = vec - math::DynamicVector<T> { 5 };
        REQUIRE(false);
    } catch (std::domain_error const& e) {
        auto const* msg = "vectors need to be the same size";
        REQUIRE((std::strcmp(e.what(), msg) == 0));
    }

    auto lhs = math::DynamicVector<T> { 3 };
    auto rhs = math::DynamicVector<T> { 3 };
    lhs[0]   = T { 1 };
    lhs[1]   = T { 2 };
    lhs[2]   = T { 3 };

    rhs[0] = T { 1 };
    rhs[1] = T { 2 };
    rhs[2] = T { 3 };

    auto stream = std::stringstream {};
    stream << lhs;
    REQUIRE(stream.str() == "1 2 3 ");

    lhs[0] = T { 4 };
    lhs[1] = T { 0 };
    lhs[2] = T { 0 };

    auto normalized = math::normalized(lhs);
    REQUIRE(normalized[0] == T { 2 });
    REQUIRE(normalized[1] == T { 0 });
    REQUIRE(normalized[2] == T { 0 });

    math::normalize(lhs);
    REQUIRE(lhs[0] == T { 2 });
    REQUIRE(lhs[1] == T { 0 });
    REQUIRE(lhs[2] == T { 0 });
}