#ifndef ARRAYD
#define ARRAYD

#include <iosfwd>
#include <cstdint>

class ArrayD {
public:
    ArrayD();
    explicit ArrayD(const std::ptrdiff_t size);
    ArrayD(const ArrayD& arrInp);
    ArrayD(ArrayD&& arrInp);

    ArrayD(const std::ptrdiff_t size, const double& rvalue);
    
    ~ArrayD() { delete [] data_; }

    ArrayD& operator=(const ArrayD& rhs);
    ArrayD& operator=(ArrayD&& rhs);
    [[nodiscard]] double& operator[](const std::ptrdiff_t index);
    [[nodiscard]] const double operator[](const std::ptrdiff_t index) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t newSize);
    void insert(const std::ptrdiff_t index, const double& value);
    void remove(const std::ptrdiff_t index);

private:
    std::ptrdiff_t ssize_{0};
    std::ptrdiff_t capacity_{0};
    double* data_{nullptr};
};

#endif
