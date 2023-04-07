#ifndef ARRAYD
#define ARRAYD

#include <iosfwd>
#include <cstdint>

class ArrayD {
public:
    ArrayD();
    explicit ArrayD(const std::ptrdiff_t size);
    ArrayD(const ArrayD& arrInp);

    ArrayD(const std::ptrdiff_t size, const double& rvalue);

    ~ArrayD() { delete [] data_; }

    ArrayD& operator=(const ArrayD& rhs);
    // double& at(const std::ptrdiff_t newIndex);
    // const double at(const std::ptrdiff_t newIndex) const;
    [[nodiscard]] double& operator[](const std::ptrdiff_t index);
    [[nodiscard]] const double operator[](const std::ptrdiff_t index) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t newSize);
    void insert(const std::ptrdiff_t index, const double& value);
    void remove(const std::ptrdiff_t index);
    // void inc_for_size() {
    //     this->resize(ssize_ + 1);
    // }
    // void push_back(const double& lvalue) noexcept;

private:
    std::ptrdiff_t ssize_{0};
    std::ptrdiff_t realSize_{0};
    double* data_{nullptr};
};

#endif
