#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayd/arrayd.hpp>

TEST_CASE("ArrayD constructor") {
    SUBCASE("Default constructor creates an empty array") {
        ArrayD arr;
        REQUIRE(arr.ssize() == 0);
    }

    SUBCASE("Constructor creates an array of a given size") {
        ArrayD arr(5);
        REQUIRE(arr.ssize() == 5);
        for (std::ptrdiff_t i = 0; i < arr.ssize(); ++i) {
            REQUIRE(arr[i] == doctest::Approx(0.0));
        }
    }

    SUBCASE("Constructor throws an exception if size is negative") {
        REQUIRE_THROWS_AS(ArrayD(-1), std::invalid_argument);
    }
}

TEST_CASE("ArrayD destructor") {
    SUBCASE("Destructor frees the memory") {
        ArrayD* arr = new ArrayD(10);
        delete arr;
    }
}

TEST_CASE("ArrayD copy constructor") {
    SUBCASE("Copy constructor creates a new array with the same elements") {
        ArrayD arr1(3);
        arr1[0] = 1.0;
        arr1[1] = 2.0;
        arr1[2] = 3.0;
        ArrayD arr2(arr1);
        REQUIRE(arr2.ssize() == 3);
        for (std::ptrdiff_t i = 0; i < arr2.ssize(); ++i) {
            REQUIRE(arr2[i] == doctest::Approx(arr1[i]));
        }
    }
}

TEST_CASE("ArrayD assignment operator") {
    SUBCASE("Assignment operator copies the elements") {
        ArrayD arr1(3);
        arr1[0] = 1.0;
        arr1[1] = 2.0;
        arr1[2] = 3.0;

        ArrayD arr2;
        arr2 = arr1;
        REQUIRE(arr2.ssize() == 3);
        for (std::ptrdiff_t i = 0; i < arr2.ssize(); ++i) {
            REQUIRE(arr2[i] == doctest::Approx(arr1[i]));
        }
    }

    SUBCASE("Assignment operator handles self-assignment") {
        ArrayD arr(3);
        arr[0] = 1.0;
        arr[1] = 2.0;
        arr[2] = 3.0;

        arr = arr;
        REQUIRE(arr.ssize() == 3);
        REQUIRE(arr[0] == doctest::Approx(1.0));
        REQUIRE(arr[1] == doctest::Approx(2.0));
        REQUIRE(arr[2] == doctest::Approx(3.0));
    }
}

TEST_CASE("ArrayD element access") {
    SUBCASE("operator[] returns a reference to the element") {
        ArrayD arr(3);
        arr[0] = 1.0;
        arr[1] = 2.0;
        arr[2] = 3.0;

        REQUIRE(&arr[0] != nullptr);
        REQUIRE(&arr[1] != nullptr);
        REQUIRE(&arr[2] != nullptr);
    }

    SUBCASE("operator[] throws an exception if the index is out of range") {
        ArrayD arr(3);
        double tmp = 0.0;
        REQUIRE_THROWS_AS(tmp = arr[-1], std::out_of_range);
        REQUIRE_THROWS_AS(tmp = arr[3], std::out_of_range);
    }

    SUBCASE("ArrayD subscript operator throws an exception when the index is out of range") {
        ArrayD arr(3);
        double tmp = 0.0;
        REQUIRE_THROWS_AS(tmp = arr[-1], std::out_of_range&);
        REQUIRE_THROWS_AS(tmp = arr[3], std::out_of_range&);
    }

    SUBCASE("ArrayD const subscript operator throws an exception when the index is out of range") {
        ArrayD arr(3);
        double tmp = 0.0;
        const ArrayD& const_arr = arr;
        REQUIRE_THROWS_AS(tmp = const_arr[-1], std::out_of_range&);
        REQUIRE_THROWS_AS(tmp = const_arr[3], std::out_of_range&);
    }    
}

TEST_CASE("ArrayD resize method throws an exception when the new size is less than or equal to 0") {
    ArrayD arr(3);
    CHECK_THROWS_AS(arr.resize(0), std::invalid_argument);
    CHECK_THROWS_AS(arr.resize(-3), std::invalid_argument);
}

// Kirills' tests


const double EPS = std::numeric_limits<double>::epsilon();

TEST_CASE("checking constuct") {
    ArrayD a(3);
    CHECK(a[1] == 0);

    ArrayD b(3, 1);
    ArrayD c(b);

    CHECK_THROWS(ArrayD(-1));

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - b[i] + 1) <= EPS);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(b[i] - c[i]) <= EPS);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(std::abs(a[i] - c[i]) <= EPS);
    }

}

TEST_CASE("checking methods") {
    ArrayD a(5, 0);

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
    CHECK(std::abs(a[5] - 0) <= EPS);
    CHECK(std::abs(a[6] - 0) <= EPS);
    CHECK(a.ssize() == 7);

    a.insert(3, 1);
    CHECK(std::abs(a[3] - 1) <= EPS);
    CHECK(std::abs(a[4] - 3) <= EPS);
    CHECK(a.ssize() == 8);

    a.remove(3);
    CHECK(std::abs(a[3] - 3) <= EPS);
    CHECK(a.ssize() == 7);

    ArrayD h(0);
    CHECK_THROWS(h.remove(0));  
}
