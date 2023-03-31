#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayd/arrayd.hpp>

TEST_CASE("basic operations") {
    ArrayD a(3);
    for(int i = 0; i < a.ssize(); ++i) {
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

TEST_CASE("resize") {
    ArrayD resize_arr(3);
    for (int i = 0; i < resize_arr.ssize(); ++i) {
        resize_arr[i] = i;
    }
    double *p1 = &resize_arr[0];
    resize_arr.resize(5);
    resize_arr[3] = 5;
    double *p2 = &resize_arr[3];
    std::cout << p1 << "\t" << p2 << '\n';
    std::cout << resize_arr[4] << '\n';
}

TEST_CASE("insert") {
    ArrayD insert_arr(4); // { 5, 6, 7, 8 }
    for (int i = 0; i < insert_arr.ssize(); ++i) {
        insert_arr[i] = i + 5;
    }
    for (int i = 0; i < insert_arr.ssize(); ++i) {
        std::cout << insert_arr[i] << ' ';
    }
    std::cout << std::endl;
    insert_arr.insert(2, 2);
    for (int i = 0; i < insert_arr.ssize(); ++i) {
        std::cout << insert_arr[i] << ' ';
    }
    std::cout << std::endl;
}

TEST_CASE("remove") {
    ArrayD remove_arr(4); // { 5, 6, 7, 8 }
    for (int i = 0; i < remove_arr.ssize(); ++i) {
        remove_arr[i] = i + 5;
    }
    for (int i = 0; i < remove_arr.ssize(); ++i) {
        std::cout << remove_arr[i] << ' ';
    }
    std::cout << std::endl;
    remove_arr.remove(2);
    for (int i = 0; i < remove_arr.ssize(); ++i) {
        std::cout << remove_arr[i] << ' ';
    }
    std::cout << std::endl;
}


// TEST_CASE("push_back") {
//     ArrayD arr(3);
//     for (int i = 0; i < arr.ssize(); ++i) {
//         arr[i] = i + 0.5;
//     }
//     for (int i = 0; i < arr.ssize(); ++i) {
//         std::cout << arr[i] << ' ';
//     }
//     std::cout << std::endl;
//     std::cout << arr.ssize() << '\n';
//     arr.push_back(1.6);
//     std::cout << arr.ssize() << '\n';
//     for (int i = 0; i < arr.ssize(); ++i) {
//         std::cout << arr[i] << ' ';
//         // std::cout << i << ' ';
//     }
//     std::cout << std::endl;
// }


/* ТЕСТЫ КИРИЛЛА */

/*
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include<arrayd/arrayd.hpp>

#include <doctest/doctest.h>

#include<iostream>

const double EPS = std::numeric_limits<double>::epsilon();

TEST_CASE("checking constuct") {
    ArrayD a(3);
    CHECK(a[1] == 0);

    ArrayD b(3, 1);
    ArrayD c(b);

    CHECK_THROWS(ArrayD(-1));

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(a[i] == b[i]-1);
    }

    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(b[i] == c[i]);
    }

    a = b;
    for (ptrdiff_t i = 0; i < 3; i += 1) {
        CHECK(a[i] == c[i]);
    }
    
}

TEST_CASE("checking methods") {
    ArrayD a(5, 0);
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;
    CHECK(a[0] - 0 <= EPS);
    CHECK(a[1] - 1 <= EPS);
    CHECK(a[2] - 2 <= EPS);
    CHECK(a[3] - 3 <= EPS);
    CHECK(a[4] - 4 <= EPS);

    CHECK(a.ssize() == 5);

    a.resize(7);
    // CHECK(a[5] - 0 <= EPS);
    // CHECK(a[6] - 0 <= EPS);
    CHECK(a.ssize() == 7);

    a.insert(1, 3);
    // CHECK(a[3] - 1 <= EPS);
    CHECK(a[4] - 3 <= EPS);
    CHECK(a.ssize() == 8);

    a.remove(3);
    CHECK(a[3] - 3 <= EPS);
    CHECK(a.ssize() == 7);

    // a.push_back(10);
    // CHECK(a[6] - 10 <= EPS);

    // a.pop_back();
    // CHECK_THROWS(a[7]);
    // CHECK_THROWS(a[15]);
    // CHECK_THROWS(a[-1]);
   
}
*/