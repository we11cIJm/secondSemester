#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>
#include <rational/rational.hpp>

TEST_CASE("[rational] - Rational ctor")
{
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));

    CHECK(Rational(3) == Rational(3, 1));
    CHECK(Rational(3) >= Rational(3, 1));
    CHECK(Rational(3) <= Rational(3, 1));
    CHECK(Rational(-10, -6) != Rational(-5, 3));
    CHECK(Rational(10, 5) > Rational(10, 6));
    CHECK(Rational(10, -7) > Rational(-10, 6));
    CHECK(Rational(5, 10) + Rational(-25, 50) <= Rational());
}

TEST_CASE("Arithmetic")
{
    CHECK(Rational(5, 6) == Rational(1, 3) + Rational(1, 2));
    CHECK(Rational(-1, 6) == Rational(1, 3) - Rational(1, 2));
    CHECK(Rational(2, 3) == Rational(1, 3) / Rational(1, 2));
    CHECK(Rational(1, 6) == Rational(1, 3) * Rational(1, 2));
}

TEST_CASE("comparisons")
{
    CHECK(Rational(1, 3) >= Rational(1, 3));
    CHECK(Rational(1, 3) <= Rational(1, 3));
    CHECK(Rational(1, 3) > Rational(1, 6));
    CHECK(Rational(1, 6) < Rational(1, 3));
}

TEST_CASE("Comparison")
{
    CHECK(true == (Rational(1, 3) == Rational(1, 3)));
    CHECK(true == (Rational(1, 3) != Rational(1, 2)));
    CHECK((Rational(1, 3) > Rational(1, 3)) == false);
    CHECK((Rational(1, 3) < Rational(1, 3)) == false);
    CHECK((Rational(1, 3) >= Rational(1, 3)) == true);
    CHECK((Rational(1, 3) <= Rational(1, 3)) == true);
    CHECK(Rational() == Rational(0));
    CHECK(Rational() == Rational(0, -1));
}

TEST_CASE("Reducing")
{
    CHECK(Rational(9, 3) == Rational(3, 1));
    CHECK(Rational(-9, 3) == Rational(-3, 1));
    CHECK(Rational(9, -3) == Rational(-3, 1));
    CHECK(Rational(-9, -3) == Rational(3, 1));
}

Rational ct = Rational(3, 9);
Rational copy_ctor = ct;
Rational c1(3, 9);
Rational c2 = -c1;
TEST_CASE("Ctor")
{
    CHECK(Rational(0) == Rational(0, 1));
    CHECK(Rational(3, 9) == ct);
    CHECK(copy_ctor == Rational(3, 9));
    std::cout << c2 << '\n';
}

TEST_CASE("unary oerations")
{
    CHECK(++Rational(1, 5) == Rational(6, 5));
    // --Rational(1, 5);
    CHECK(Rational(1, 5)++ == Rational(1, 5));
    // --Rational(1, 5);
    CHECK(--Rational(1, 5) == Rational(-4, 5));
    // ++Rational(1, 5);
    CHECK(Rational(1, 5)-- == Rational(1, 5));
    // ++Rational(1, 5);

    CHECK(++Rational(-1, 5) == Rational(4, 5));
    --Rational(-1, 5);
    CHECK(Rational(-1, 5)++ == Rational(-1, 5));
    --Rational(-1, 5);
    CHECK(--Rational(-1, 5) == Rational(-6, 5));
    ++Rational(-1, 5);
    CHECK(Rational(-1, 5)-- == Rational(-1, 5));
    ++Rational(-1, 5);

    CHECK(++Rational(5) == Rational(6, 1));
    --Rational(5);
    CHECK(Rational(5)++ == Rational(5, 1));
    --Rational(5);
    CHECK(--Rational(5) == Rational(4, 1));
    ++Rational(5);
    CHECK(Rational(5)-- == Rational(5, 1));
    ++Rational(5);
}

Rational ratt(4, 10); // 2/5
int32_t int1 = 2;
int32_t int2 = -1;
int32_t int3 = 0;

TEST_CASE("int arithmetics")
{
    CHECK(ratt + int1 == Rational(12, 5));
    CHECK(ratt - int1 == Rational(-8, 5));
    CHECK(ratt * int1 == Rational(4, 5));
    CHECK(int1 * ratt == Rational(4, 5));
    CHECK(ratt / int1 == Rational(1, 5));
    CHECK(int1 / ratt == Rational(5, 1));

    CHECK(ratt + int2 == Rational(-3, 5));
    CHECK(ratt - int2 == Rational(7, 5));
    CHECK(ratt * int2 == Rational(-2, 5));
    CHECK(int2 * ratt == Rational(-2, 5));
    CHECK(ratt / int2 == Rational(-2, 5));
    CHECK(int2 / ratt == Rational(-5, 2));

    CHECK(ratt + int3 == Rational(2, 5));
    CHECK(ratt - int3 == Rational(2, 5));
    CHECK(ratt * int3 == Rational(0));
    CHECK(int3 * ratt == Rational());
    CHECK(int3 / ratt == Rational(0));
    CHECK_THROWS(ratt / int3 == Rational());
}

TEST_CASE("compound assignment")
{
    CHECK(Rational(5, 6) == (Rational(1, 2) += Rational(1, 3)));
    CHECK(Rational(1, 2) + 2 == Rational(5, 2));
    CHECK(Rational(5, 2) == (Rational(1, 2) += 2));
    CHECK(-2 != (Rational(1, 2) += Rational(-3, 2)));
    CHECK(Rational(1) == 1);

    CHECK(Rational(1, 6) == (Rational(1, 2) -= Rational(1, 3)));
    CHECK(Rational(1, 6) == (Rational(1, 2) *= Rational(1, 3)));
    CHECK(Rational(3, 2) == (Rational(1, 2) /= Rational(1, 3)));
}

// TEST_CASE("i/o test") {
//     Rational test1;
//     Rational test2;
//     try {
//         std::cin >> test1 >> test2;
//         // std::cout << test1 << std::endl;
//         // std::cout << test2 << std::endl;
//         // std::cout << (test1 == test2) << '\n';
//         CHECK_THROWS(test1 / test2 );
//     } catch(const std::exception& ex) {
//         std::cerr << ex.what() << '\n';
//     }
// }

TEST_CASE("Test Rational default constructor") {
    const Rational r;
    CHECK(r.GetNum() == 0);
    CHECK(r.GetDen() == 1);
}

TEST_CASE("Test Rational constructor from one integer") {
    const Rational r(5);
    CHECK(r.GetNum() == 5);
    CHECK(r.GetDen() == 1);
}

TEST_CASE("Test Rational constructor from two integers") {
    const Rational r(3, 5);
    CHECK(r.GetNum() == 3);
    CHECK(r.GetDen() == 5);
    const Rational r2(-7, 2);
    CHECK(r2.GetNum() == -7);
    CHECK(r2.GetDen() == 2);
}

TEST_CASE("Test Rational operator+=") {
    Rational r(3, 4);
    r += Rational(1, 4);
    CHECK(r.GetNum() == 1);
    CHECK(r.GetDen() == 1);
}

TEST_CASE("Test Rational operator-=") {
    Rational r(1, 2);
    r -= Rational(1, 4);
    CHECK(r.GetNum() == 1);
    CHECK(r.GetDen() == 4);
}

TEST_CASE("Test Rational operator*=") {
    Rational r(3, 4);
    r *= Rational(2, 5);
    CHECK(r.GetNum() == 3);
    CHECK(r.GetDen() == 10);
}

TEST_CASE("Test Rational operator/=") {
    Rational r(3, 4);
    r /= Rational(2, 5);
    CHECK(r.GetNum() == 15);
    CHECK(r.GetDen() == 8);
}

TEST_CASE("Test Rational operator++") {
    Rational r(3, 4);
    ++r;
    CHECK(r.GetNum() == 7);
    CHECK(r.GetDen() == 4);
}

TEST_CASE("Test Rational operator--") {
    Rational r(5, 4);
    --r;
    CHECK(r.GetNum() == 1);
    CHECK(r.GetDen() == 4);
}

TEST_CASE("Test Rational operator==") {
    const Rational r1(3, 4);
    const Rational r2(6, 8);
    CHECK(r1 == r2);
    CHECK(r1 == Rational(3, 4));
}

TEST_CASE("Test Rational operator!=") {
    const Rational r1(3, 4);
    const Rational r2(1, 4);
    CHECK(r1 != r2);
    CHECK(r1 != 0.25);
}

TEST_CASE("Test Rational operator<") {
    const Rational r1(2, 5);
    const Rational r2(3, 5);
    CHECK(r1 < r2);
    CHECK(r1 < Rational(3, 5));
}

TEST_CASE("Test Rational operator>") {
    const Rational r1(2, 5);
    const Rational r2(3, 5);
    CHECK(r2 > r1);
    CHECK(r2 > 0.4);
}

TEST_CASE("Test Rational operator<=") {
    const Rational r1(2, 5);
    const Rational r2(3, 5);
    CHECK(r1 <= r2);
    CHECK(r1 <= Rational(1, 2));
}

TEST_CASE("Test Rational operator>=") {
    const Rational r1(2, 5);
    const Rational r2(3, 5);
    CHECK(r2 >= r1);
    CHECK(r2 >= 0.6);
}

TEST_CASE("Test Rational operator<<") {
    const Rational r(3, 5);
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == "3/5");
}

TEST_CASE("Test Rational operator>>") {
    Rational r;
    std::stringstream ss("7/9");
    ss >> r;
    // r.ReadFrom(ss);
    CHECK(r.GetNum() == 7);
    CHECK(r.GetDen() == 9);
    // CHECK(Rational(7, 9) == r);
}

