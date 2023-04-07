#include <iostream>
#include <sstream>
#include <arrayd/arrayd.hpp>

ArrayD::ArrayD()
    :
    ssize_(0),
    realSize_(0),
    data_(nullptr) {
}
ArrayD::ArrayD(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("size is negative");
    } else if (size > 0) {
        ssize_ = size;
        realSize_ = ssize_ * 2;
        data_ = new double[realSize_];
        for(int i = 0; i < realSize_; ++i) { // or i < ssize_ ? (i did this because other data can be filled by trash)
            data_[i] = 0;
        }
    } else {
        ssize_ = 0;
        realSize_ = 0;
        data_ = nullptr;
    }

}
ArrayD::ArrayD(const ArrayD& arrInp)
    :
    ssize_(arrInp.ssize_), 
    realSize_(arrInp.ssize_ * 2),
    data_(new double[realSize_]) {
        for(int i = 0; i < ssize_; ++i) {
            data_[i] = arrInp.data_[i];
        }
}
ArrayD::ArrayD(const std::ptrdiff_t size, const double& rvalue)
    :
    ssize_(size),
    realSize_(ssize_ * 2),
    data_(new double[realSize_]) {
        for (int i = 0; i < ssize_; ++i) {
            data_[i] = rvalue;
        }
}
ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    if(this != &rhs) { /* a != a : checking that it isn't the same object */
        delete [] data_;
        ssize_ = rhs.ssize_;
        realSize_ = rhs.ssize_ * 2;
        data_ = new double[realSize_];
        for(int i = 0; i < rhs.ssize_; ++i) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

double& ArrayD::operator[](const std::ptrdiff_t index) { /* write method */
    if(index >= ssize_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return *(data_ + index); // return &data_[i];
}
const double ArrayD::operator[](const std::ptrdiff_t index) const { /* read-only method */
    if(index >= ssize_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return *(data_ + index); // значение <return *(data_ + index)> или константную ссылку <return &data_[i];> (конструктор move)
}

std::ptrdiff_t ArrayD::ssize() const noexcept {
    return ssize_;
}

void ArrayD::resize(const std::ptrdiff_t newSize) {
    // double *pNewData = data_ + ssize_;
    if (newSize <= 0) {
        throw std::invalid_argument("size cannot be negative or null");
    }
    if (newSize > realSize_) {
        realSize_ = newSize * 2;
        double *pNewData = new double[realSize_];
        for (ptrdiff_t i = 0; i < this->ssize_; ++i) {
            pNewData[i] = data_[i];
        }
        for (ptrdiff_t i = this->ssize_; i < newSize; ++i) {
            pNewData[i] = 0;
        }
        delete [] data_;
        data_ = pNewData;
    }
    ssize_ = newSize;
}

void ArrayD::insert(const std::ptrdiff_t index, const double& value) {
    if (index >= ssize_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    if (ssize_ + 1 <= realSize_) {
        ssize_ += 1;
    } else {
        resize(ssize_ + 1);
    }
    
    for (ptrdiff_t i = ssize_; i > index; --i) {
        data_[i] = data_[i-1];
    }
    data_[index] = value;
}

void ArrayD::remove(const std::ptrdiff_t index) {
    if (index >= ssize_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    for (ptrdiff_t i = index; i < ssize_; ++i) {
        data_[i] = data_[i+1];
    }
    ssize_ -= 1;
}

// void ArrayD::push_back(const double& lvalue) noexcept {
//     ssize_ += 1;
//     data_[ssize_ - 1] = lvalue;
// }

