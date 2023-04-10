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
    std::ptrdiff_t size_{0};
    std::ptrdiff_t capacity_{0};
    T* data_{nullptr};
};

template<typename T>
ArrayT<T>::ArrayT()
    : size_(0),
    capacity_(0),
    data_(nullptr)
{}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("size cannot be negative");
    } else if (size == 0) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = size;
        capacity_ = size_ * 2;
        data_ = new T[capacity_]{};
    }
}

// may be different type of array?
template<typename T>
ArrayT<T>::ArrayT(const ArrayT& arrInp)
    : size_(arrInp.size_), capacity_(arrInp.size_ * 2) {
    data_ = new T[capacity_]{};
    for(std::ptrdiff_t i = 0; i < arrInp.size_; ++i) {
        data_[i] = arrInp.data_[i];
    }
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size, const T& rvalue)
    :
    size_(size),
    capacity_(size_ * 2) {
        data_ = new T[capacity_]{};
        for (std::ptrdiff_t i = 0; i < size_; ++i) {
            data_[i] = rvalue;
        }
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT& rhs) {
    if (this != &rhs) {
        delete[] data_;
        size_ = rhs.size_;
        capacity_ = rhs.size_ * 2;
        data_ = new T[capacity_]{};
        for (std::ptrdiff_t i = 0; i < rhs.size_; ++i) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t index) {
    if (index >= size_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + index);
}

template<typename T>
const T ArrayT<T>::operator[](const std::ptrdiff_t index) const {
    if (index >= size_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    return *(data_ + index);
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return size_;
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t newSize) {
    if (newSize <= 0) {
        throw std::invalid_argument("size cannot be negative or null");
    }
    if (newSize > capacity_) {
        capacity_ = newSize * 2;
        T *pNewData = new T[capacity_]{};
        for (std::ptrdiff_t i = 0; i < this->size_; ++i) {
            pNewData[i] = data_[i];
        }
        delete[] data_;
        data_ = pNewData;
    }
    size_ = newSize;
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t index, const T& value) {
    if (size_ + 1 <= capacity_) {
        size_ += 1;
    } else {
        resize(size_ + 1);
    }
    for (std::ptrdiff_t i = size_; i > index; --i) {
        data_[i] = data_[i-1];
    }
    data_[index] = value;
}

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t index) {
    if (index >= size_ || index < 0) {
        throw std::invalid_argument("out of range");
    }
    for (std::ptrdiff_t i = index; i < size_; ++i) {
        data_[i] = data_[i+1];
    }
    size_ -= 1;
}

#endif