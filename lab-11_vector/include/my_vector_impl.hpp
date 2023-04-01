#pragma once

#include <regex>
#include "my_vector.hpp"

#define usingT template<class T>

namespace containers {
    usingT
    my_vector<T>::my_vector() {
        capacity_ = 1;
        size_ = 0;
        array_ = (T *) (new char[sizeof(T) * capacity_]);
    }

    usingT
    my_vector<T>::my_vector(std::size_t n) {
        capacity_ = n;
        size_ = n;
        array_ = (T *) new char[sizeof(T) * capacity_];
        for (int i = 0; i < capacity_; i++)
            new(array_ + i) T();
    }

    usingT
    my_vector<T>::my_vector(const my_vector &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = (T *) (new char[sizeof(T) * capacity_]);
        for (size_t i = 0; i < size_; i++) {
            new(array_ + i) T(other[i]);
        }
    }

    usingT
    my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other) {
        if (this == &other)
            return *this;
        my_vector<T> t = other;
        swap(&t, this);
        return *this;
    }

    usingT
    void my_vector<T>::destroy_vector() {
        for (size_t i = 0; i < size_; i++) {
            array_[i].~T();
        }
        delete[] (char *) (array_);

    }

    usingT
    my_vector<T>::~my_vector() {
        destroy_vector();
    }

    usingT
    size_t my_vector<T>::size() {
        return size_;
    }

    usingT
    size_t my_vector<T>::capacity() {
        return capacity_;
    }

    usingT
    bool my_vector<T>::empty() {
        return size_ == 0;
    }


}