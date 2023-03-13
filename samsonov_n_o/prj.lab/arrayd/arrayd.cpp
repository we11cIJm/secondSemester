#include <iostream>
#include <sstream>
#include <arrayd/arrayd.hpp>

ArrayD::ArrayD(const std::ptrdiff_t ssizeInp) : ssize_(ssizeInp), data_(new double[ssizeInp]) {} /* ctor with input size */
ArrayD::ArrayD(const ArrayD & arrInp) : ssize_(arrInp.ssize_), data_(new double[ssize_]) { /* copy ctor */
    for(int i = 0; i < ssize_; ++i) {
        data_[i] = arrInp.data_[i]; /* assigment of values */
    }
}
ArrayD& ArrayD::operator=(const ArrayD & rhs) {
    if(this != &rhs) { /* a != a : not the same object */
        delete [] data_; /* removing existing memory */
        ssize_ = rhs.ssize_; /* assign size of lhs ( or *this) object */
        data_ = new double[ssize_]; /* creating memory area for new array*/
        for(int i = 0; i < ssize_; ++i) {
            data_[i] = rhs.data_[i]; /*assigment of values*/
        }
    }
    return *this;
}

double& ArrayD::operator[](const std::ptrdiff_t index) { /* write method */
    if(index >= this->ssize_ || index < 0) {
        throw std::invalid_argument("segmentation fault");
    }
    return *(data_ + index);
}
const double ArrayD::operator[](const std::ptrdiff_t index) const { /* read-only method */
    if(index >= this->ssize_ || index < 0) {
        throw std::invalid_argument("segmentation fault");
    }
    return *(data_ + index);
}

std::ptrdiff_t ArrayD::GetSize() const noexcept {
    return ssize_;
}
void ArrayD::Resize(const std::ptrdiff_t newSize) {
    double *pNewData = new double[newSize]; /* allocate memory for a new array */
    std::ptrdiff_t nSize = newSize < ssize_ ? newSize : ssize_;
    for(int i = 0; i < nSize; ++i) {
        pNewData[i] = data_[i];
    }
    delete [] data_;
    ssize_ = newSize;
    data_ = pNewData;
}

