#include <iosfwd>
#include <sstream>
#include "arrayD.hpp"

/*
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}
*/

ArrayD::ArrayD(const ptrdiff_t ssizeInp) : ssize_(ssizeInp), data_(new double[ssizeInp]) {} // ctor with input size
ArrayD::ArrayD(ArrayD const& arrInp) : ssize_(arrInp.ssize_), data_(new double[ssize_]) { // copy ctor
    for(int i = 0; i < ssize_; ++i) {
        data_[i] = arrInp.data_[i]; // assigment of values
    }
}
ArrayD& ArrayD::operator=(const ArrayD& rhs) { //
    if(this != &rhs) { // a != a : not the same object
        delete [] data_; // removing existing memory
        ssize_ = rhs.ssize_; // assign size of rhs object
        data_ = new double[ssize_]; // creating memory area for new array
        for(int i = 0; i < ssize_; ++i) {
            data_[i] = rhs.data_[i]; // assigment of values
        }
    }
    return *this;
}

double& ArrayD::operator[](const ptrdiff_t index) { // write index
    return *(data_ + index);
}
const double ArrayD::operator[](const ptrdiff_t index) const { // read index
    return *(data_ + index);
}

ptrdiff_t ArrayD::getSize() const noexcept {
    return ssize_;
}
void ArrayD::resize(const ptrdiff_t newSize) {
    double *pNewData = new double[newSize];
    ptrdiff_t nSize = newSize < ssize_ ? newSize : ssize_;
    for(int i = 0; i < nSize; ++i) {
        pNewData[i] = data_[i];
    }
    delete [] data_;
    ssize_ = newSize;
    data_ = pNewData;
}

