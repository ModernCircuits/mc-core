// SPDX-License-Identifier: BSL-1.0

#include <mc/core/array.hpp>
#include <mc/core/initializer_list.hpp>
#include <mc/core/iterator.hpp>
#include <mc/core/utility.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("iterator.hpp: data", "[iterator]", char, short, int)
{
    using namespace mc;

    using T = TestType;
    T cArray[16]{};  // NOLINT(*-avoid-c-arrays)
    REQUIRE(data(cArray) == &cArray[0]);
    REQUIRE(size(cArray) == 16U);
    REQUIRE_FALSE(empty(cArray));

    auto stdArray = std::array<T, 8>{};
    REQUIRE(size(stdArray) == stdArray.size());
    REQUIRE(data(stdArray) == stdArray.data());
    REQUIRE(data(std::as_const(stdArray)) == std::as_const(stdArray).data());
    REQUIRE_FALSE(empty(stdArray));

    auto iList = {T(), T()};
    REQUIRE(data(iList) != nullptr);
    REQUIRE_FALSE(empty(iList));
}
