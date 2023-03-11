#include <rational/rational.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

Rational a(3);
Rational b(3, 1);

TEST_CASE("[rational] - Rational ctor")
{
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));
    
    CHECK(a == b);
    CHECK(a >= b);
    CHECK(a <= b);
    CHECK(Rational(-10, -6) != Rational(-5, 3));
    CHECK(Rational(10, 5) > Rational(10, 6));
    CHECK(Rational(10, -7) > Rational(-10, 6));
    CHECK(Rational(5, 10) + Rational(-25, 50) <= Rational());
}

Rational rat1(1, 3);
Rational rat2(1, 2);

Rational sum(5, 6);
Rational diff(-1, 6);
Rational divv(2, 3);
Rational mul(1, 6);


TEST_CASE("Arithmetic") {
  CHECK(sum == rat1 + rat2);
  CHECK(diff == rat1 - rat2);
  CHECK(divv == rat1 / rat2);
  CHECK(mul == rat1 * rat2);
}

bool equal = true;
Rational rat3 = rat1;
Rational rat6(1, 6);

TEST_CASE("123") {
  CHECK(rat1 >= rat3);
  CHECK(rat1 <= rat3);
  CHECK(rat1 > rat6);
  CHECK(rat6 < rat3);
}

TEST_CASE("Comparison") {
  CHECK(equal == (rat1 == rat3));
  CHECK(equal == (rat1 != rat2));
  CHECK((rat1 > rat3) == false);
  CHECK((rat1 < rat3) == false);
  CHECK((rat1 >= rat3) == true);
  CHECK((rat1 <= rat3) == true);
}

Rational rat4(9, 3);
Rational rat5(3, 1);

TEST_CASE("Reducing") {
  CHECK(rat4 == rat5);
}

Rational a2(0);
Rational a1(0, 1);
Rational b2(3, 9);
Rational b1 = b2;

TEST_CASE("Ctor") {
  CHECK(a2 == a1);
  CHECK(b2 == b1);
}
