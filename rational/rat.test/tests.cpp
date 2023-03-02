#include "rational/rational.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

Rational rat1(1, 3);
Rational rat2(1, 2);
//Rational rat3(1, 0);

Rational summary(5, 6);
Rational difference(-1, 6);
Rational division(2, 3);
Rational multiplication(1, 6);

TEST_CASE("Arithmetic")
{
  CHECK(summary == rat1 + rat2);
  CHECK(difference == rat1 - rat2);
  CHECK(division == rat1 / rat2);
  CHECK(multiplication == rat1 * rat2);
//  CHECK_THROWS(rat3);
}

Rational v1(1, 2);
Rational v2(2, 4);
Rational v3(-1, 2);

TEST_CASE("Equality")
{
    CHECK(v1 == v2);
    CHECK(v1 != v3);
    CHECK(v2 != v3);
}

Rational c1(1);
Rational c2(1, 1);

TEST_CASE("Ctors")
{
    CHECK(c1 == c2);
}

