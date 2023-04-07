#ifndef ARRAYT
#define ARRAYT

#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstddef>

template<typename T>
class ArrayT {
public:
    ArrayT();
    explicit ArrayT(const std::ptrdiff_t size);
    ArrayT(const ArrayT& arrInp);

    ArrayT(const std::ptrdiff_t size, const T& rvalue); // no realization fot this method

    ~ArrayT() { delete[] data_; }

    ArrayT& operator=(const ArrayT& rhs);
    // double& at(const std::ptrdiff_t newIndex);
    // const double at(const std::ptrdiff_t newIndex) const;
    [[nodiscard]] T& operator[](const std::ptrdiff_t index);
    [[nodiscard]] const T operator[](const std::ptrdiff_t index) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t newSize);
    void insert(const std::ptrdiff_t index, const T& value);
    void remove(const std::ptrdiff_t index);
    // void push_back(const double& lvalue) noexcept;

private:
    std::ptrdiff_t ssize_{0};
    std::ptrdiff_t realSize_{0};
    T* data_{nullptr};
};

template<typename T>
ArrayT<T>::ArrayT()
    : ssize_(0),
    realSize_(0),
    data_(nullptr)
{}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("size cannot be negative");
    } else if (size == 0) {
        ssize_ = 0;
        realSize_ = 0;
        data_ = nullptr;
    } else {
        ssize_ = size;
        realSize_ = ssize_ * 2;
        data_ = new T[realSize_]{};
        for (ptrdiff_t i = 0; i < ssize_; ++i) {
            data_[i] = 0;
        }
    }
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& arrInp)
    : ssize_(arrInp.ssize_),
    realSize_(arrInp.ssize_ * 2) {
        data_ = new T[realSize_]{};
        for(ptrdiff_t i = 0; i < arrInp.ssize_; ++i) {
            data_[i] = arrInp.data_[i];
        }
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size, const T& rvalue)
    :
    ssize_(size),
    realSize_(ssize_ * 2) {
        data_ = new T[realSize_]{};
        for (int i = 0; i < ssize_; ++i) {
            data_[i] = rvalue;
        }
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT& rhs) {
    if (this != &rhs) {
        ssize_ = rhs.ssize_;
        if (this->realSize_ < rhs.realSize_) {
            realSize_ = rhs.realSize_;
        }
        for (ptrdiff_t i = 0; i < rhs.ssize(); ++i) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t index) {
    if (index >= ssize_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + index);
}

template<typename T>
const T ArrayT<T>::operator[](const std::ptrdiff_t index) const {
    if (index >= ssize_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + index);
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize()const noexcept {
    return ssize_;
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t newSize) {
    if (newSize <= 0) {
        throw std::invalid_argument("size cannot be negative or null");
    }
    if (newSize > realSize_) {
        realSize_ = newSize * 2;
        T *pNewData = new T[realSize_]{};
        for (ptrdiff_t i = 0; i < this->ssize_; ++i) {
            pNewData[i] = data_[i];
        }
        for (ptrdiff_t i = 0; i < newSize; ++i) {
            pNewData[i] = 0;
        }
        delete [] data_;
        data_ = pNewData;
    }
    ssize_ = newSize;
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t index, const T& value) {
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

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t index) {
    if (index >= ssize_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    for (ptrdiff_t i = index; i < ssize_; ++i) {
        data_[i] = data_[i+1];
    }
    ssize_ -= 1;
}

#endif