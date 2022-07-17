#include "mc/math.hpp"

#include "mc/sstream.hpp"

#include <catch2/catch_template_test_macros.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/dense: DynamicMatrix", "[math][dense][matrix]", float, double, long double)
{
    using T = TestType;

    auto mat = math::DynamicMatrix<T> {};
    REQUIRE(mat.rows() == 0);
    REQUIRE(mat.cols() == 0);
    REQUIRE(mat.size() == 0);
    REQUIRE(!math::isNonZero(mat));

    mat.resize(2, 2);
    REQUIRE(mat.rows() == 2);
    REQUIRE(mat.cols() == 2);
    REQUIRE(mat.size() == 4);

    REQUIRE(!math::isNonZero(mat));
    REQUIRE(mat.at(0, 0) == T { 0 });
    REQUIRE(mat.at(0, 1) == T { 0 });
    REQUIRE(mat.at(1, 0) == T { 0 });
    REQUIRE(mat.at(1, 1) == T { 0 });

    // REQUIRE_THROWS_AS(mat.at(2, 0), std::out_of_range);
    // REQUIRE_THROWS_AS(mat.at(0, 2), std::out_of_range);
    // REQUIRE_THROWS_AS(mat.at(2, 2), std::out_of_range);

    auto const& cmat = mat;
    REQUIRE(cmat.at(0, 0) == T { 0 });
    REQUIRE(cmat.at(0, 1) == T { 0 });
    REQUIRE(cmat.at(1, 0) == T { 0 });
    REQUIRE(cmat.at(1, 1) == T { 0 });

    // REQUIRE_THROWS_AS(cmat.at(2, 0), std::out_of_range);
    // REQUIRE_THROWS_AS(cmat.at(0, 2), std::out_of_range);
    // REQUIRE_THROWS_AS(cmat.at(2, 2), std::out_of_range);

    mat(0, 0) = T { 0 };
    mat(0, 1) = T { 1 };
    mat(1, 0) = T { 2 };
    mat(1, 1) = T { 3 };

    REQUIRE(math::isNonZero(mat));

    auto stream = std::stringstream {};
    stream << mat;
    REQUIRE(stream.str() == "0 1 \n2 3 \n");

    auto const& constMat = mat;
    REQUIRE(constMat(0, 0) == T { 0 });
    REQUIRE(constMat(0, 1) == T { 1 });
    REQUIRE(constMat(1, 0) == T { 2 });
    REQUIRE(constMat(1, 1) == T { 3 });

    auto scaled = mat * T { 2 };
    REQUIRE(scaled(0, 0) == T { 0 });
    REQUIRE(scaled(0, 1) == T { 2 });
    REQUIRE(scaled(1, 0) == T { 4 });
    REQUIRE(scaled(1, 1) == T { 6 });

    auto scaledTwice = T { 2 } * scaled;
    REQUIRE(scaledTwice(0, 0) == T { 0 });
    REQUIRE(scaledTwice(0, 1) == T { 4 });
    REQUIRE(scaledTwice(1, 0) == T { 8 });
    REQUIRE(scaledTwice(1, 1) == T { 12 });

    auto addScaler = T { 2 } + mat;
    REQUIRE(addScaler(0, 0) == T { 2 });
    REQUIRE(addScaler(0, 1) == T { 3 });
    REQUIRE(addScaler(1, 0) == T { 4 });
    REQUIRE(addScaler(1, 1) == T { 5 });

    auto subScaler = T { 2 } - mat;
    REQUIRE(subScaler(0, 0) == T { -2 });
    REQUIRE(subScaler(0, 1) == T { -1 });
    REQUIRE(subScaler(1, 0) == T { 0 });
    REQUIRE(subScaler(1, 1) == T { 1 });

    REQUIRE(addScaler != subScaler);

    auto summedMatrix = addScaler + subScaler;
    REQUIRE(summedMatrix(0, 0) == T { 0 });
    REQUIRE(summedMatrix(0, 1) == T { 2 });
    REQUIRE(summedMatrix(1, 0) == T { 4 });
    REQUIRE(summedMatrix(1, 1) == T { 6 });

    auto subMatrix = addScaler - subScaler;
    REQUIRE(subMatrix(0, 0) == T { 4 });
    REQUIRE(subMatrix(0, 1) == T { 4 });
    REQUIRE(subMatrix(1, 0) == T { 4 });
    REQUIRE(subMatrix(1, 1) == T { 4 });

    REQUIRE(subMatrix != math::DynamicMatrix<T> {});

    mat.clear();
    REQUIRE(mat(0, 0) == T { 0 });
    REQUIRE(mat(0, 1) == T { 0 });
    REQUIRE(mat(1, 0) == T { 0 });
    REQUIRE(mat(1, 1) == T { 0 });
}

TEMPLATE_TEST_CASE("math/dense: DynamicMatrixFunctions", "[math][dense][matrix]", float, double, long double)
{
    using T = TestType;

    auto s  = math::DynamicMatrix<T> { 2, 2 };
    s(0, 0) = T { 0 };
    s(0, 1) = T { 0 };
    s(1, 0) = T { 1 };
    s(1, 1) = T { 1 };

    math::swapRow(s, 0, 1);
    REQUIRE(s(0, 0) == T { 1 });
    REQUIRE(s(0, 1) == T { 1 });
    REQUIRE(s(1, 0) == T { 0 });
    REQUIRE(s(1, 1) == T { 0 });

    REQUIRE_THROWS_AS(math::swapRow(s, 0, 2), std::out_of_range);

    auto multi  = math::DynamicMatrix<T> { 2, 2 };
    multi(0, 0) = T { 0 };
    multi(0, 1) = T { 0 };
    multi(1, 0) = T { 1 };
    multi(1, 1) = T { 1 };

    math::multiplyRow(multi, 0, T { 2 });
    math::multiplyRow(multi, 1, T { 2 });
    REQUIRE(multi(0, 0) == T { 0 });
    REQUIRE(multi(0, 1) == T { 0 });
    REQUIRE(multi(1, 0) == T { 2 });
    REQUIRE(multi(1, 1) == T { 2 });

    REQUIRE_THROWS_AS(math::multiplyRow(multi, 2, T { 2 }), std::out_of_range);

    auto multiAdd  = math::DynamicMatrix<T> { 2, 2 };
    multiAdd(0, 0) = T { 0 };
    multiAdd(0, 1) = T { 0 };
    multiAdd(1, 0) = T { 1 };
    multiAdd(1, 1) = T { 1 };

    math::multiplyAddRow(multiAdd, 1, 0, T { 2 });
    REQUIRE(multiAdd(0, 0) == T { 2 });
    REQUIRE(multiAdd(0, 1) == T { 2 });
    REQUIRE(multiAdd(1, 0) == T { 1 });
    REQUIRE(multiAdd(1, 1) == T { 1 });

    REQUIRE_THROWS_AS(math::multiplyAddRow(multiAdd, 2, 0, T { 2 }), std::out_of_range);

    auto maxRow  = math::DynamicMatrix<T> { 2, 2 };
    maxRow(0, 0) = T { 1 };
    maxRow(0, 1) = T { 1 };
    maxRow(1, 0) = T { 0 };
    maxRow(1, 1) = T { 0 };

    REQUIRE(math::findRowWithMaxElement(maxRow, 0, 0) == 0);
    REQUIRE(math::findRowWithMaxElement(maxRow, 0, 1) == 1);

    // try {
    //     math::findRowWithMaxElement(maxRow, 0, 2);
    //     REQUIRE(false);
    // } catch (std::exception const& e) {
    //     auto const* msg = "row index out of bounds";
    //     REQUIRE((std::strcmp(e.what(), msg) == 0));
    // }

    // try {
    //     math::findRowWithMaxElement(maxRow, 2, 0);
    //     REQUIRE(false);
    // } catch (std::exception const& e) {
    //     auto const* msg = "column index out of bounds";
    //     REQUIRE((std::strcmp(e.what(), msg) == 0));
    // }

    auto split  = math::DynamicMatrix<T> { 2, 2 };
    split(0, 0) = T { 1 };
    split(0, 1) = T { 1 };
    split(1, 0) = T { 0 };
    split(1, 1) = T { 0 };

    auto splits = math::splitColumns(split, 1);
    REQUIRE(splits.first.rows() == 2);
    REQUIRE(splits.first.cols() == 1);

    REQUIRE(splits.second.rows() == 2);
    REQUIRE(splits.second.cols() == 1);

    // try {
    //     REQUIRE(math::splitColumns(split, 2).first.size() == 0);
    //     REQUIRE(false);
    // } catch (std::exception const& e) {
    //     auto const* msg = "column index out of bounds";
    //     REQUIRE((std::strcmp(e.what(), msg) == 0));
    // }

    auto joinA  = math::DynamicMatrix<T> { 2, 2 };
    joinA(0, 0) = T { 1 };
    joinA(1, 0) = T { 1 };
    joinA(0, 1) = T { 0 };
    joinA(1, 1) = T { 0 };
    auto joinB  = math::DynamicMatrix<T> { 2, 1 };
    joinB(0, 0) = T { 1 };
    joinB(1, 0) = T { 1 };

    auto joinedA = math::join(joinA, joinB);
    REQUIRE(joinedA.rows() == 2);
    REQUIRE(joinedA.cols() == 3);
    REQUIRE(joinedA(0, 0) == T { 1 });
    REQUIRE(joinedA(1, 0) == T { 1 });
    REQUIRE(joinedA(0, 1) == T { 0 });
    REQUIRE(joinedA(1, 1) == T { 0 });
    REQUIRE(joinedA(0, 2) == T { 1 });
    REQUIRE(joinedA(1, 2) == T { 1 });

    auto joinC  = math::DynamicMatrix<T> { 2, 2 };
    joinA(0, 0) = T { 1 };
    joinA(1, 0) = T { 1 };
    joinA(0, 1) = T { 0 };
    joinA(1, 1) = T { 0 };
    auto joinD  = math::DynamicMatrix<T> { 2, 2 };
    joinB(0, 0) = T { 1 };
    joinB(1, 0) = T { 1 };

    auto joinedB = math::join(joinC, joinD);
    REQUIRE(joinedB.rows() == 2);
    REQUIRE(joinedB.cols() == 4);

    REQUIRE_THROWS_AS(math::join(joinA, math::DynamicMatrix<T> { 3, 1 }), std::invalid_argument);

    auto identityA = math::DynamicMatrix<T> { 2, 2 };
    math::makeIdentity(identityA);
    identityA(0, 0) = T { 1 };
    identityA(1, 0) = T { 0 };
    identityA(0, 1) = T { 0 };
    identityA(1, 1) = T { 1 };

    auto identityB  = math::makeIdentity<math::DynamicMatrix<T>>(3);
    identityB(0, 0) = T { 1 };
    identityB(1, 0) = T { 0 };
    identityB(0, 1) = T { 0 };
    identityB(1, 1) = T { 1 };
    identityB(2, 2) = T { 1 };

    auto identityC = math::DynamicMatrix<T> { 2, 1 };
    REQUIRE_THROWS_AS(math::makeIdentity(identityC), std::invalid_argument);

    auto invertA  = math::DynamicMatrix<T> { 3, 3 };
    invertA(0, 0) = T { 2 };
    invertA(0, 1) = T { 1 };
    invertA(0, 2) = T { 1 };
    invertA(1, 0) = T { 1 };
    invertA(1, 1) = T { 0 };
    invertA(1, 2) = T { 1 };
    invertA(2, 0) = T { 0 };
    invertA(2, 1) = T { 3 };
    invertA(2, 2) = T { 1 };

    auto const invA = math::inverse(invertA);
    REQUIRE(invA(0, 0) == T { 0.75 });
    REQUIRE(invA(0, 1) == T { -0.5 });
    REQUIRE(invA(0, 2) == T { -0.25 });
    REQUIRE(invA(1, 0) == T { 0.25 });
    REQUIRE(invA(1, 1) == T { -0.5 });
    REQUIRE(invA(1, 2) == T { 0.25 });
    REQUIRE(invA(2, 0) == T { -0.75 });
    REQUIRE(invA(2, 1) == T { 1.5 });
    REQUIRE(invA(2, 2) == T { 0.25 });

    auto sub = math::subMatrix(invertA, 0, 0);
    REQUIRE(math::isSquare(sub));
    REQUIRE(sub.rows() == 2);
    REQUIRE(sub(0, 0) == T { 0 });
    REQUIRE(sub(0, 1) == T { 1 });
    REQUIRE(sub(1, 0) == T { 3 });
    REQUIRE(sub(1, 1) == T { 1 });

    REQUIRE(math::determinant(invertA) == T { -4 });

    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(2)));
    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(3)));
    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(4)));
    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(5)));
    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(6)));
    REQUIRE(math::isRowEchelon(math::makeIdentity<math::DynamicMatrix<T>>(7)));

    auto a  = math::DynamicMatrix<T> { 3, 4 };
    a(0, 0) = T { 1 };
    a(0, 1) = T { 3 };
    a(0, 2) = T { -1 };
    a(0, 3) = T { 13 };
    a(1, 0) = T { 4 };
    a(1, 1) = T { -1 };
    a(1, 2) = T { 1 };
    a(1, 3) = T { 9 };
    a(2, 0) = T { 2 };
    a(2, 1) = T { 4 };
    a(2, 2) = T { 3 };
    a(2, 3) = T { -6 };
    math::rowEchelon(a);
    REQUIRE(math::isRowEchelon(a));
    REQUIRE(math::rank(a) == 3);
    REQUIRE(math::isNonZero(a));

    a.resize(3, 3);
    a(0, 0) = T { 0 };
    a(0, 1) = T { 0 };
    a(0, 2) = T { 1 };
    a(1, 0) = T { 1 };
    a(1, 1) = T { 0 };
    a(1, 2) = T { 1 };
    a(2, 0) = T { 0 };
    a(2, 1) = T { 0 };
    a(2, 2) = T { 1 };
    REQUIRE(math::rank(a) == 2);
    REQUIRE(math::isNonZero(a));
}
