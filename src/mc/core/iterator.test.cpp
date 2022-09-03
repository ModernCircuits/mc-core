// SPDX-License-Identifier: BSL-1.0

#include <mc/core/array.hpp>
#include <mc/core/initializer_list.hpp>
#include <mc/core/iterator.hpp>
#include <mc/core/utility.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("iterator.hpp: data", "[iterator]", char, short, int)
{
    using T = TestType;
    T cArray[16]{};  // NOLINT(*-avoid-c-arrays)
    REQUIRE(mc::data(cArray) == &cArray[0]);
    REQUIRE(mc::size(cArray) == 16U);
    REQUIRE_FALSE(mc::empty(cArray));

    auto stdArray = std::array<T, 8>{};
    REQUIRE(mc::size(stdArray) == stdArray.size());
    REQUIRE(mc::data(stdArray) == stdArray.data());
    REQUIRE(mc::data(mc::as_const(stdArray)) == mc::as_const(stdArray).data());
    REQUIRE_FALSE(mc::empty(stdArray));

    auto iList = {T(), T()};
    REQUIRE(mc::data(iList) != nullptr);
    REQUIRE_FALSE(mc::empty(iList));
}