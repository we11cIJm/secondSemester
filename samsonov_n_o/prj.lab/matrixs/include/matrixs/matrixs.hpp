#ifndef MATRIX_S
#define MATRIX_S

#include <iostream>
#include <cstdint>

class MatrixS {
public:
    // MatrixS() = default;
    // MatrixS(const size_t size = {0, 0});
    // MatrixS(const MatrixS& t); //
    // MatrixS& operator=(const MatrixS& rhs);

    /**
     * \brief возвращает элемент матрицы под индексами {i, j}
     * \throw std::out_of_range если хотябы один индекс вне диапазона [0, dsize)
     * \param[in] elem индексы элемента
     * \return элемент матрицы
     */
//    [[nodiscard]] int& at(const size_type elem);
//    [[nodiscard]] int at(const size_type elem) const;

    /**
     * \return текущий размер матрицы {m, n}
     */
//    [[nodiscard]] size_type ssize() const noexcept;

    /**
     * \brief Изменение размера матрицы
     * \param[in] new_size новый размер матрицы {m, n}
     * \throw std::invalid_argument если new m <= 0 или new n <= 0
     */
    // void resize(const size_t new_size);

private:
    // using size_type = std::pair<std::ptrdiff_t row, std::ptrdiff_t column> MatrixS;
};

#endif