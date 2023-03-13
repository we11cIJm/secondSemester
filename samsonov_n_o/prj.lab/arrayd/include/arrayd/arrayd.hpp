#ifndef ARRAYD
#define ARRAYD

#include <iosfwd>
#include <cstdint>

class ArrayD {
public:
    ArrayD() = default; /* default ctor */
    ArrayD(const std::ptrdiff_t sizeInp);
    ArrayD(const ArrayD & arrInp);
    ~ArrayD() { delete [] data_; }  /* dctor - removing memory */

    ArrayD& operator=(const ArrayD& rhs);
    double& at(const std::ptrdiff_t newIndex);
    const double at(const std::ptrdiff_t newIndex) const;
    double& operator[](const std::ptrdiff_t index);
    const double operator[](const std::ptrdiff_t index) const;

    std::ptrdiff_t GetSize() const noexcept;
    void Resize(const std::ptrdiff_t newSize);

private:
    std::ptrdiff_t ssize_{0};
    double* data_{nullptr};
};

#endif