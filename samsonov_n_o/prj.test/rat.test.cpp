#include <rational/rational.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


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
    CHECK(-1 == (Rational(1, 2) += Rational(-3, 2)));

    CHECK(Rational(1, 6) == (Rational(1, 2) -= Rational(1, 3)));
    CHECK(Rational(1, 6) == (Rational(1, 2) *= Rational(1, 3)));
    CHECK(Rational(3, 2) == (Rational(1, 2) /= Rational(1, 3)));
}

/*TEST_CASE("i/o test") {
    Rational test1;
    Rational test2;
    try {
        std::cin >> test1; //>> test2;
        std::cout << test1 << std::endl;
        // std::cout << test2 << std::endl;
        // std::cout << (test1 == test2) << '\n';
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << '\n';
    }
}
*/