#include <matrixs/matrixs.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Constructor with default arguments") {
    MatrixS m;
    CHECK(m.nRows() == 0);
    CHECK(m.nCols() == 0);
}

TEST_CASE("Constructor with size argument") {
    MatrixS m(std::make_tuple(2, 3));
    CHECK(m.nRows() == 2);
    CHECK(m.nCols() == 3);
}

TEST_CASE("Constructor with row and column arguments") {
    MatrixS m(2, 3);
    CHECK(m.nRows() == 2);
    CHECK(m.nCols() == 3);
}

TEST_CASE("Copy constructor") {
    MatrixS m1(2, 3);
    m1.at({0, 0}) = 1;
    m1.at({0, 1}) = 2;
    m1.at({0, 2}) = 3;
    m1.at({1, 0}) = 4;
    m1.at({1, 1}) = 5;
    m1.at({1, 2}) = 6;

    MatrixS m2(m1);
    CHECK(m2.nRows() == 2);
    CHECK(m2.nCols() == 3);
    CHECK(m2.at({0, 0}) == 1);
    CHECK(m2.at({0, 1}) == 2);
    CHECK(m2.at({0, 2}) == 3);
    CHECK(m2.at({1, 0}) == 4);
    CHECK(m2.at({1, 1}) == 5);
    CHECK(m2.at({1, 2}) == 6);
}

TEST_CASE("Copy assignment operator") {
    MatrixS m1(std::make_tuple(2, 3));
    m1.at({0, 0}) = 1;
    m1.at({0, 1}) = 2;
    m1.at({0, 2}) = 3;
    m1.at({1, 0}) = 4;
    m1.at({1, 1}) = 5;
    m1.at({1, 2}) = 6;

    MatrixS m2;
    m2 = m1;
    CHECK(m2.nRows() == 2);
    CHECK(m2.nCols() == 3);
    CHECK(m2.at({0, 0}) == 1);
    CHECK(m2.at({0, 1}) == 2);
    CHECK(m2.at({0, 2}) == 3);
    CHECK(m2.at({1, 0}) == 4);
    CHECK(m2.at({1, 1}) == 5);
    CHECK(m2.at({1, 2}) == 6);
}

TEST_CASE("at() method with tuple argument") {
    MatrixS m(std::make_tuple(2, 3));
    m.at({0, 0}) = 1;
    m.at({0, 1}) = 2;
    m.at({0, 2}) = 3;
    m.at({1, 0}) = 4;
    m.at({1, 1}) = 5;
    m.at({1, 2}) = 6;

    CHECK(m.at({0, 0}) == 1);
    CHECK(m.at({0, 1}) == 2);
    CHECK(m.at({0, 0}) == 1);
	CHECK(m.at({0, 1}) == 2);
	CHECK(m.at({0, 2}) == 3);
	CHECK(m.at({1, 0}) == 4);
	CHECK(m.at({1, 1}) == 5);
	CHECK(m.at({1, 2}) == 6);
	
    int t = 0;

	// Test out of range exceptions
	CHECK_THROWS_AS(t = m.at({-1, 0}), std::out_of_range);
	CHECK_THROWS_AS(t = m.at({0, -1}), std::out_of_range);
	CHECK_THROWS_AS(t = m.at({2, 0}), std::out_of_range);
	CHECK_THROWS_AS(t = m.at({0, 3}), std::out_of_range);
	
	// Test const version of the method
	const MatrixS cm(std::make_tuple(2, 3));
	const int& c = cm.at({0, 0});
	CHECK(c == 0); // default value is 0
}

TEST_CASE("at() method with two int arguments") {
    MatrixS m(std::make_tuple(2, 3));
    m.at(0, 0) = 1;
    m.at(0, 1) = 2;
    m.at(0, 2) = 3;
    m.at(1, 0) = 4;
    m.at(1, 1) = 5;
    m.at(1, 2) = 6;

    CHECK(m.at(0, 0) == 1);
    CHECK(m.at(0, 1) == 2);
    CHECK(m.at(0, 2) == 3);
    CHECK(m.at(1, 0) == 4);
    CHECK(m.at(1, 1) == 5);
    CHECK(m.at(1, 2) == 6);

    int t = 0;

    CHECK_THROWS_AS(t = m.at(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, -1), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(2, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, 3), std::out_of_range);
}

TEST_CASE("const at() method with tuple argument") {
    const MatrixS m(std::make_tuple(2, 3));
    CHECK(m.at({0, 0}) == 0);
    CHECK(m.at({0, 1}) == 0);
    CHECK(m.at({0, 2}) == 0);
    CHECK(m.at({1, 0}) == 0);
    CHECK(m.at({1, 1}) == 0);
    CHECK(m.at({1, 2}) == 0);

    int t = 0;

    CHECK_THROWS_AS(t = m.at(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, -1), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(2, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, 3), std::out_of_range);
}

TEST_CASE("const at() method with two int arguments") {
    const MatrixS m(std::make_tuple(2, 3));
    CHECK(m.at(0, 0) == 0);
    CHECK(m.at(0, 1) == 0);
    CHECK(m.at(0, 2) == 0);
    CHECK(m.at(1, 0) == 0);
    CHECK(m.at(1, 1) == 0);
    CHECK(m.at(1, 2) == 0);

    int t = 0;

    CHECK_THROWS_AS(t = m.at(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, -1), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(2, 0), std::out_of_range);
    CHECK_THROWS_AS(t = m.at(0, 3), std::out_of_range);
}

// need to fix and uncomment 186, 

/*TEST_CASE("Resize method") {
    //MatrixS m({2, 3});
    //std::cout << "Initial size: " << std::get<0>(m.ssize()) << " x " << std::get<1>(m.ssize()) << std::endl;
    //m.resize({4, 5});
    //std::cout << "Resized size: " << std::get<0>(m.ssize()) << " x " << std::get<1>(m.ssize()) << std::endl;

    MatrixS m(std::make_tuple(2, 3));

    m.resize(std::make_tuple(4, 5));
    CHECK(m.ssize() == std::make_tuple(4, 5));
    CHECK(m.nRows() == 4);
    CHECK(m.nCols() == 5);

    m.resize(1, 1);
    CHECK(m.ssize() == std::make_tuple(1, 1));
    CHECK(m.nRows() == 1);
    CHECK(m.nCols() == 1);

    CHECK_THROWS(m.resize(-2, 3));
    CHECK_THROWS(m.resize(2, -3));
    CHECK_THROWS(m.resize(-2, -3));
}*/

TEST_CASE("ssize() method") {
    MatrixS m(std::make_tuple(2, 3));

    CHECK(m.ssize() == std::make_tuple(2, 3));

    /*m.resize(std::make_tuple(3, 4));

    CHECK(m.ssize() == {3, 4});*/
}

TEST_CASE("nRows() method") {
    MatrixS m(std::make_tuple(2, 3));

    CHECK(m.nRows() == 2);

    m.resize({3, 4});

    CHECK(m.nRows() == 3);
}

TEST_CASE("nCols() method") {
    MatrixS m(std::make_tuple(2, 3));

    CHECK(m.nCols() == 3);

    m.resize({3, 4});

    CHECK(m.nCols() == 4);
}
