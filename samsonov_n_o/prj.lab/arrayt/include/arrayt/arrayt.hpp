#ifndef ARRAYT
#define ARRAYT

#include <iostream>
#include <sstream>
#include <cstdint>

template<typename T>
class ArrayT {
public:
    ArrayT();
    ArrayT(const std::ptrdiff_t size);
    ArrayT(const ArrayT& arrInp); // copy ctor

    ArrayT(const std::ptrdiff_t size, const int& rvalue);

    ~ArrayT() { delete [] data_; }

    ArrayT& operator=(const ArrayT& rhs);
    
    [[nodiscard]] T& operator[](const std::ptrdiff_t index);
    [[nodiscard]] const T operator[](const std::ptrdiff_t index) const;
    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    void resize(const std::ptrdiff_t newSize);
    void insert(const std::ptrdiff_t index, const T& value);
    void remove(const std::ptrdiff_t index);
    // void inc_for_size() {
    //     this->resize(ssize_ + 1);
    // }
    void push_back(const T& lvalue) noexcept;

private:
    std::ptrdiff_t ssize_{0};
    std::ptrdiff_t realSize_{0};
    T* data_{nullptr};
};

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) 
    :
    ssize_(size),
    realSize_(ssize_ * 2),
    data_(new T[realSize_]) {
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& arrInp)
    :
    ssize_(arrInp.ssize_), 
    realSize_(arrInp.realSize_),
    data_(new T[realSize_]) {
        for(int i = 0; i < ssize_; ++i) {
            data_[i] = arrInp.data_[i];
        }
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size, const int& rvalue)
    :
    ssize_(size),
    realSize_(ssize_ * 2),
    data_(new T[realSize_]) {
        for (int i = 0; i < ssize_; ++i) {
            data_[i] = rvalue;
        }
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT& rhs) {
    if(this != &rhs) { /* a != a : checking that it isn't the same object */
        delete [] data_;
        ssize_ = rhs.ssize_;
        realSize_ = ssize_ * 2;
        data_ = new T[realSize_];
        for(int i = 0; i < ssize_; ++i) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t index) { /* write method */
    if(index >= ssize_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return *(data_ + index); // return &data_[i];
}

template<typename T>
const T ArrayT<T>::operator[](const std::ptrdiff_t index) const { /* read-only method */
    if(index >= ssize_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return *(data_ + index); // значение <return *(data_ + index)> или константную ссылку <return &data_[i];> (конструктор move)
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return ssize_;
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t newSize) {
    // T *pNewData = data_ + ssize_;
    if (newSize > realSize_) {
        // pNewData = new T[newSize - ssize_];
        // pNewData = data_;
        realSize_ = newSize * 2;
        T* pNewData = new T[realSize_];
        for (ptrdiff_t i = 0; i < newSize; ++i) {
            pNewData[i] = data_[i];
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
    if (index >= 0 && index < ssize_) {
        for (ptrdiff_t i = index; i < ssize_ - 1; ++i) {
            data_[i] = data_[i+1];
        }
        ssize_ -= 1;
    } else {
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
void ArrayT<T>::push_back(const T& lvalue) noexcept {
    ssize_ += 1;
    data_[ssize_ - 1] = lvalue;
}

// std::ostream& operator<<(std::ostream ostrm, const ArrayT& rhs);
// std::istream& operator>>(std::ostream ostrm, const ArrayT& rhs);

#endif
