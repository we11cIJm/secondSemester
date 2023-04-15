#include <iostream>
#include <cstdint>
#include <cmath>
#include <matrixs/matrixs.hpp>

/******************** constructors ********************/

// ctor with tuple
MatrixS::MatrixS(const SizeType& size) {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("size cannot be negative");
    }
    rows_ = std::get<0>(size);
    cols_ = std::get<1>(size);
    data_ = new int[rows_ * cols_]{};
}

// ctor with count of rows (m) and columns (n)
MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("size cannot be negative");
    }
    rows_ = m;
    cols_ = n;
    data_ = new int[rows_ * cols_]{};
}

// copy ctor
MatrixS::MatrixS(const MatrixS& other) {
    if (this != &other) {
        if (rows_ <= other.rows_ || cols_ <= other.cols_) {
            delete[] data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = new int[rows_ * cols_]{};
        }
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }
}

// dctor
MatrixS::~MatrixS() {
    delete[] data_;
}


/******************** methods  ********************/

// method 'size' for returning size of the matrix in {m n} form
const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return std::make_tuple(rows_, cols_); // is it right?
}

// method 'nRows' for returning count of rows in matrix
std::ptrdiff_t MatrixS::nRows() const noexcept {
    return rows_;
}

// method 'nCols' for returning count of columns in matrix
std::ptrdiff_t MatrixS::nCols() const noexcept {
    return cols_;
}

// method 'at' for writing a value with tuple
int& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) < 0 ||
        std::get<1>(elem) < 0 ||
        std::get<0>(elem) >= rows_ ||
        std::get<1>(elem) >= cols_
       ) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + std::get<0>(elem) * std::get<1>(elem));
}

// same as above for reading (and there's structured bindings, since C++17)
const int& MatrixS::at(const SizeType& elem) const {
    auto [row, col] = elem;
    if (row < 0 ||
        col < 0 ||
        row >= rows_ ||
        col >= cols_
       ) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + row * col);
}

// method 'at' for writing a value with indexes
int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row < 0 ||
        col < 0 ||
        row >= rows_ ||
        col >= cols_
       ) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + row * col);
}

// same as method above for reading
const int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) const {
    if (row < 0 ||
        col < 0 ||
        row >= rows_ ||
        col >= cols_
       ) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + row * col);
}

// method 'resize' for changing a size of matrix with tuple
void MatrixS::resize(const SizeType& new_size) {
    auto [row, col] = new_size;
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("size cannot be negative or zero");
    }
    if (row > rows_ || col > cols_) {
        int* pNewData = new int[row * col]{};
        std::copy(data_, data_ + rows_ * cols_, pNewData);
        delete[] data_;
        data_ = pNewData;
    }
    rows_ = row;
    cols_ = col;
}

// method 'resize' for changing a size of matrix with indexes
void MatrixS::resize(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("size cannot be negative or zero");
    }
    if (row > rows_ || col > cols_) {
        int* pNewData = new int[row * col]{};
        std::copy(data_, data_ + rows_ * cols_, pNewData);
        delete[] data_;
        data_ = pNewData;
    }
    rows_ = row;
    cols_ = col;
}
