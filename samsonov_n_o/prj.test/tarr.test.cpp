#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayt/arrayt.hpp>

/*TEST_CASE("basic operations") {
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
}*/

// Kirills' tests

const double EPS = std::numeric_limits<double>::epsilon();

TEST_CASE("checking constuct") {
    ArrayT<double> a(3);
    CHECK(a[1] == 0);

    ArrayT<double> b(3, 1);
    ArrayT<double> c(b);

    CHECK_THROWS(ArrayT<double>(-1));

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i]- b[i]+1)<=EPS);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(b[i] - c[i])<=EPS);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - c[i])<=EPS);
    }
    
}

TEST_CASE("checking methods") {
    ArrayT<double> a(5, 0);
    a[1] = 1.0;
    a[2] = 2.0;
    a[3] = 3.0;
    a[4] = 4.0;
    CHECK(std::abs(a[0] - 0) <= EPS);
    CHECK(std::abs(a[1] - 1) <= EPS);
    CHECK(std::abs(a[2] - 2) <= EPS);
    CHECK(std::abs(a[3] - 3) <= EPS);
    CHECK(std::abs(a[4] - 4) <= EPS);

    CHECK(a.ssize() == 5);

    a.resize(7);
/*
/home/kolya/Desktop/code/secondSemester/samsonov_n_o/prj.test/tarr.test.cpp:103: ERROR: CHECK( std::abs(a[5] - 0) <= EPS ) is NOT correct!
  values: CHECK( 3.09293e+262 <= 2.22045e-16 )

/home/kolya/Desktop/code/secondSemester/samsonov_n_o/prj.test/tarr.test.cpp:104: ERROR: CHECK( std::abs(a[6] - 0) <= EPS ) is NOT correct!
  values: CHECK( 5.78091e+204 <= 2.22045e-16 )
*/
    // CHECK(std::abs(a[5] - 0) <= EPS);
    // CHECK(std::abs(a[6] - 0) <= EPS);
    CHECK(a.ssize() == 7);

    a.insert(3, 1);
    CHECK(std::abs(a[3] - 1) <= EPS);
    CHECK(std::abs(a[4] - 3) <= EPS);
    CHECK(a.ssize() == 8);

    a.remove(3);
    CHECK(std::abs(a[3] - 3) <= EPS);
    CHECK(a.ssize() == 7);

    // a.push_back(10);
    // CHECK(std::abs(a[7] - 10) <= EPS);

    // a.insert(8, 11);
    // CHECK(a[8] - 11 <= EPS);
    // a.pop_back();
    // a.pop_back();

    // CHECK_THROWS(a[7]);
    // CHECK_THROWS(a[15]);
    // CHECK_THROWS(a[-1]);
    // CHECK_THROWS(a.resize(0));
    // CHECK_THROWS(a.insert(8, 2));
    // CHECK_THROWS(a.insert(-1, 2));
    // CHECK_THROWS(a.remove(-1));
    // CHECK_THROWS(a.remove(7));

    ArrayT<double> h(0);
    CHECK_THROWS(h.remove(0));

}

TEST_CASE_TEMPLATE("numeric variable", ArrayT, int, double, long long, ptrdiff_t) {
    ArrayT var = ArrayT();
    var -= 1;
    CHECK(var == -1);
}
