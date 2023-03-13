#include <arrayd/arrayd.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("123") {
    ArrayD a(3);
    for(int i = 0; i < a.GetSize(); ++i) {
        a[i] = (double)i + 0.5;
    }
    // for(int i = 0; i < 3; ++i) {
    //     CHECK(a[i] == (double)i + 0.5);
    // }
    // CHECK(a[1] == 1.5);
    double num = 1.4;
    CHECK_THROWS(a[5] = num);
    CHECK_THROWS(a[-1] = 1.5);
}