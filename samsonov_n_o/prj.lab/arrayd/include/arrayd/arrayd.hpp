#ifndef ARRAYD
#define ARRAYD

#include <iosfwd>
#include <cstdint>

class ArrayD {
public:
    ArrayD();
    ArrayD(const std::ptrdiff_t size);
    ArrayD(const ArrayD& arrInp);
    ~ArrayD() { delete [] data_; }

    ArrayD& operator=(const ArrayD& rhs);
    // double& at(const std::ptrdiff_t newIndex);
    // const double at(const std::ptrdiff_t newIndex) const;
    [[nodiscard]] double& operator[](const std::ptrdiff_t index);
    [[nodiscard]] const double operator[](const std::ptrdiff_t index) const;

    [[nodiscard]] std::ptrdiff_t GetSize() const noexcept;
    void Resize(const std::ptrdiff_t newSize);
    void insert(const std::ptrdiff_t index, const double& value);
    void remove(const std::ptrdiff_t index);

private:
    std::ptrdiff_t ssize_{0};
    std::ptrdiff_t realSize_{0};
    double* data_{nullptr};
};

// std::ostream& operator<<(std::ostream ostrm, const ArrayD& rhs);
// std::istream& operator>>(std::ostream ostrm, const ArrayD& rhs);

#endif
