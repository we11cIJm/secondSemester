#include <arrayd/arrayd.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("basic operations") {
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

TEST_CASE("resize") {
    ArrayD resize_arr(3);
    for (int i = 0; i < resize_arr.GetSize(); ++i) {
        resize_arr[i] = i;
    }
    double *p1 = &resize_arr[0];
    resize_arr.Resize(5);
    resize_arr[3] = 5;
    double *p2 = &resize_arr[3];
    std::cout << p1 << "\t" << p2 << '\n';
    std::cout << resize_arr[4] << '\n';
}

// TEST_CASE("insert") {
//     ArrayD insert_arr(4); // { 5, 6, 7, 8 }
//     for (int i = 0; i < insert_arr.GetSize(); ++i) {
//         insert_arr[i] = i + 5;
//     }
//     for (int i = 0; i < insert_arr.GetSize(); ++i) {
//         std::cout << insert_arr[i] << ' ';
//     }
//     std::cout << std::endl;
//     insert_arr.insert(2, 2);
//     for (int i = 0; i < insert_arr.GetSize(); ++i) {
//         std::cout << insert_arr[i] << ' ';
//     }
//     std::cout << std::endl;
// }

TEST_CASE("remove") {
    ArrayD remove_arr(4); // { 5, 6, 7, 8 }
    for (int i = 0; i < remove_arr.GetSize(); ++i) {
        remove_arr[i] = i + 5;
    }
    for (int i = 0; i < remove_arr.GetSize(); ++i) {
        std::cout << remove_arr[i] << ' ';
    }
    std::cout << std::endl;
    remove_arr.remove(2);
    for (int i = 0; i < remove_arr.GetSize(); ++i) {
        std::cout << remove_arr[i] << ' ';
    }
    std::cout << std::endl;
}