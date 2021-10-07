#include "mc/units/Frequency.hpp"

#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE(
    "stl/units: Frequency<integral>", "[stl][units]", int, long, long long)
{
    using T         = TestType;
    using Hertz     = mc::Hertz<T>;
    using Kilohertz = mc::Kilohertz<T>;
    using BPM       = mc::BPM<T>;

    REQUIRE(Hertz(1).count() == T(1));
    REQUIRE(Kilohertz(1).count() == T(1));

    REQUIRE(Hertz { Kilohertz(1) }.count() == T(1'000));
    REQUIRE(BPM { Hertz(1) }.count() == T(60));

    REQUIRE(Hertz { T(1) } + Hertz { T(1) } == Hertz { T(2) });
    REQUIRE(Hertz { T(1) } + Hertz { T(2) } == Hertz { T(3) });
    REQUIRE(Hertz { T(1) } - Hertz { T(1) } == Hertz { T(0) });
    REQUIRE(Hertz { T(2) } * T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / Hertz { T(2) } == T(1));
    REQUIRE(T(2) * Hertz { T(2) } == Hertz { T(4) });

    REQUIRE(Hertz { T(1) } != Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } < Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } <= Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } > Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } >= Kilohertz { T(1) });
    REQUIRE(Hertz { T(1'000) } == Kilohertz { T(1) });

    auto a = Hertz(T(1));
    a += Hertz(T(1));
    REQUIRE(a.count() == T(2));
    a -= Hertz(T(1));
    REQUIRE(a.count() == T(1));
    a *= T(4);
    REQUIRE(a.count() == T(4));
    a /= T(2);
    REQUIRE(a.count() == T(2));

    REQUIRE(mc::frequencyCast<Hertz>(Hertz { T(1) }).count() == T(1));
    REQUIRE(mc::frequencyCast<Hertz>(Kilohertz { T(1) }).count() == T(1'000));
    REQUIRE(mc::frequencyCast<Kilohertz>(Hertz { T(1'000) }).count() == T(1));
    REQUIRE(mc::frequencyCast<BPM>(Hertz { T(1) }).count() == T(60));
    REQUIRE(mc::frequencyCast<Hertz>(BPM { T(120) }).count() == T(2));
    REQUIRE(mc::frequencyCast<Kilohertz>(BPM { T(120'000) }).count() == T(2));

    using TwoThirdHertz = mc::Frequency<T, std::ratio<2, 3>>;
    REQUIRE(mc::frequencyCast<Hertz>(TwoThirdHertz { T(3) }).count() == T(2));
    REQUIRE(mc::frequencyCast<Hertz>(TwoThirdHertz { T(6) }).count() == T(4));
    REQUIRE(mc::frequencyCast<Hertz>(TwoThirdHertz { T(12) }).count() == T(8));

    REQUIRE(mc::floor<Kilohertz>(Hertz { T(4'000) }) == Kilohertz { T(4) });
    REQUIRE(mc::floor<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(4) });

    REQUIRE(mc::ceil<Kilohertz>(Hertz { T(5'000) }) == Kilohertz { T(5) });
    REQUIRE(mc::ceil<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(5) });
    REQUIRE(mc::ceil<Kilohertz>(Hertz { T(4'400) }) == Kilohertz { T(5) });

    REQUIRE(mc::round<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(5) });
    REQUIRE(mc::round<Kilohertz>(Hertz { T(4'500) }) == Kilohertz { T(4) });
    REQUIRE(mc::round<Kilohertz>(Hertz { T(4'499) }) == Kilohertz { T(4) });

    REQUIRE(mc::toHertz(BPM { T(60) }) == Hertz { T(1) });
    REQUIRE(mc::toHertz(BPM { T(120) }) == Hertz { T(2) });
    REQUIRE(mc::toHertz(BPM { T(180) }) == Hertz { T(3) });

    REQUIRE(mc::toBPM(Hertz { T(1) }) == BPM { T(60) });
    REQUIRE(mc::toBPM(Hertz { T(2) }) == BPM { T(120) });
    REQUIRE(mc::toBPM(Hertz { T(3) }) == BPM { T(180) });

    REQUIRE((+Hertz(1)).count() == T(+1));
    REQUIRE((-Hertz(1)).count() == T(-1));

    REQUIRE(abs(Hertz { T(4) }) == Hertz { T(4) });
    REQUIRE(abs(Hertz { T(-4) }) == Hertz { T(4) });
}

TEMPLATE_TEST_CASE("stl/units: Frequency<floating_point>", "[stl][units]",
    float, double, long double)
{
    using T         = TestType;
    using Hertz     = mc::Hertz<T>;
    using Kilohertz = mc::Kilohertz<T>;
    using BPM       = mc::BPM<T>;

    REQUIRE(Hertz(T(1)).count() == T(1));
    REQUIRE(Kilohertz(T(1)).count() == T(1));
    REQUIRE((+Hertz(T(1))).count() == T(+1));
    REQUIRE((-Hertz(T(1))).count() == T(-1));

    REQUIRE(Hertz { Kilohertz(T(1)) }.count() == T(1'000));
    REQUIRE(BPM { Hertz(T(1)) }.count() == T(60));

    REQUIRE(Hertz { T(1) } + Hertz { T(1) } == Hertz { T(2) });
    REQUIRE(Hertz { T(1) } + Hertz { T(2) } == Hertz { T(3) });
    REQUIRE(Hertz { T(1) } - Hertz { T(1) } == Hertz { T(0) });
    REQUIRE(Hertz { T(2) } * T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / Hertz { T(2) } == T(1));
    REQUIRE(T(2) * Hertz { T(2) } == Hertz { T(4) });

    REQUIRE(Hertz { T(1) } != Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } < Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } <= Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } > Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } >= Kilohertz { T(1) });
    REQUIRE(Hertz { T(1'000) } == Kilohertz { T(1) });

    auto a = Hertz(T(1));
    a += Hertz(T(1));
    REQUIRE(a.count() == T(2));
    a -= Hertz(T(1));
    REQUIRE(a.count() == T(1));
    a *= T(4);
    REQUIRE(a.count() == T(4));
    a /= T(2);
    REQUIRE(a.count() == T(2));

    using mc::frequencyCast;
    REQUIRE(frequencyCast<Hertz>(Hertz { T(1) }).count() == T(1));
    REQUIRE(frequencyCast<Hertz>(Kilohertz { T(1) }).count() == T(1'000));
    REQUIRE(frequencyCast<Kilohertz>(Hertz { T(1'000) }).count() == T(1));
    REQUIRE(frequencyCast<BPM>(Hertz { T(1) }).count() == T(60));
    REQUIRE(frequencyCast<Hertz>(BPM { T(120) }).count() == T(2));
    REQUIRE(frequencyCast<Kilohertz>(BPM { T(120'000) }).count() == T(2));

    REQUIRE(mc::abs(Hertz { T(4) }) == Hertz { T(4) });
    REQUIRE(mc::abs(Hertz { T(-4) }) == Hertz { T(4) });
}