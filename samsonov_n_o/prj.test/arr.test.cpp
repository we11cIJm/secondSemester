#include<arrayd/arrayd.hpp>
// #include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("123") {
    ArrayD a(3);
    for(int i = 0; i < a.getSize(); ++i) {
        a[i] = i;
    }
    // try {
    //     for(int i = 0; i < 3; ++i) {
    //         if(i != a[i]) {
    //             throw "not working";
    //         }
    //     }
    // }
    // catch (const char * ex) {
    //     std::cout << "catch block is on" << '\n';
    // }
    for(int i = 0; i < 3; ++i) {
        CHECK_THROWS(a[i] == i);
    }
}

// int main() {
//     ArrayD a(3);
//     for(int i = 0; i < a.getSize(); ++i) {
//         a[i] = i;
//     }
//     try {
//         for(int i = 0; i < 3; ++i) {
//             if(i + 1 != a[i]) {
//                 throw "not working";
//             }
//         }
//     }
//     catch (const char * ex) {
//         std::cout << "catch block is on" << '\n';
//     }

// }