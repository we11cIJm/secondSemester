#ifndef ARRAYD
#define ARRAYD

#include <iosfwd>
#include <cstddef> 
#include <cstdint>

/*
<iosfwd> doesn't contain type ptrdiff_t,
but <iostream> does
<cstddef> - lib for ptrdiff_t type
*/

class ArrayD {
public:
    ArrayD() = default; // default ctor
    ArrayD(const ptrdiff_t sizeInp);
    ArrayD(ArrayD const& arrInp);
    ~ArrayD() { delete [] data_; }  // dctor - removing memory

    ArrayD& operator=(const ArrayD& rhs);
    double& operator[](const ptrdiff_t index);
    const double operator[](const ptrdiff_t index) const;

    ptrdiff_t getSize() const noexcept;
    void resize(const ptrdiff_t newSize);

private:
    ptrdiff_t ssize_{0};
    double* data_{nullptr};
};

#endif