#ifndef MATRIX_S
#define MATRIX_S

#include <iostream>
#include <cstdint>
#include <cstddef>
#include <tuple>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

public:
    MatrixS();
    explicit MatrixS(const SizeType& size);

    //explicit MatrixS(std::initializer_list<std::size_t> size)
    //: MatrixS(std::make_tuple(*(size.begin()), *(size.begin() + 1))) {}
    
    MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n);
    ~MatrixS();

    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    [[nodiscard]] int& at(const SizeType& elem);
    [[nodiscard]] const int& at(const SizeType& elem) const;
    [[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    [[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;
 
    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    [[nodiscard]] const SizeType& ssize() const noexcept;

    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;

private:
    int* data_{0};
    std::ptrdiff_t rows_{0};
    std::ptrdiff_t cols_{0};
    SizeType size_{std::make_tuple(rows_, cols_)};
};
#endif
