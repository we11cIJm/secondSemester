#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayt/arrayt.hpp>

TEST_CASE("basic operations") {
    SUBCASE("initialize with size") {
        ArrayT<int> arr(10);
        ArrayT<int> a(3);
        CHECK(a.ssize() == 3);
        for(int i = 0; i < a.ssize(); ++i) {
            CHECK(a[i] == 0);
        }
    }
    SUBCASE("access elements") {
        ArrayT<int> a(3);
        for(int i = 0; i < a.ssize(); ++i) {
            a[i] = i + 1;
        }
        CHECK(a[0] == 1);
        CHECK(a[1] == 2);
        CHECK(a[2] == 3);
        CHECK_THROWS(a[-1] == 0);
        CHECK_THROWS(a[3] == 0);
    }
    SUBCASE("resize") {
        ArrayT<int> a(3);
        a.resize(5);
        CHECK(a.ssize() == 5);
        for(int i = 0; i < a.ssize(); ++i) {
            CHECK(a[i] == 0);
        }
    }
    // 0400
    SUBCASE("insert") {
        ArrayT<int> a(3);
        a.insert(1, 4);
        CHECK(a.ssize() == 4);
        CHECK(a[0] == 0);
        CHECK(a[1] == 4);
        CHECK_FALSE(a[2] == 1);
        CHECK_FALSE(a[3] == 2);
        CHECK_THROWS(a[-1] == 0);
        CHECK_THROWS(a[4] == 0);
    }
    SUBCASE("remove") {
        ArrayT<int> a(4);
        for(int i = 0; i < a.ssize(); ++i) {
            a[i] = i + 1;
        }
        a.remove(1);
        CHECK(a.ssize() == 3);
        CHECK(a[0] == 1);
        CHECK(a[1] == 3);
        CHECK(a[2] == 4);
        CHECK_THROWS(a[-1] == 0);
        CHECK_THROWS(a[3] == 0);
    }
}
