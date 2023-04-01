#pragma once

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
        static_assert(std::is_default_constructible<T>::value);
        capacity_ = n;
        size_ = n;
        array_ = (T *) new char[sizeof(T) * capacity_];
        for (size_t i = 0; i < capacity_; i++)
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
    size_t my_vector<T>::size() const {
        return size_;
    }

    usingT
    size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    usingT
    bool my_vector<T>::empty() const {
        return size_ == 0;
    }

    usingT
    size_t my_vector<T>::calc_capacity(size_t n) {
        size_t ans = 1;
        while (ans < n)
            ans *= 2;
        return ans;
    }

    usingT
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_)
            return;
        size_t new_capacity = calc_capacity(n);
        T *new_array = (T *) (new char[sizeof(T) * new_capacity]);
        for (size_t i = 0; i < size_; i++) {
            new(new_array + i) T(array_[i]);
            array_[i].~T();
        }
        capacity_ = new_capacity;
        delete[] (char *) array_;
        array_ = new_array;
    }

    usingT
    void my_vector<T>::resize(std::size_t n) {
        static_assert(std::is_default_constructible<T>::value);
        reserve(n);
        while (size_ > n) {
            array_[size_ - 1].~T();
            size_--;
        }
        while (size_ < n) {
            new(array_ + size_)T();
            size_++;
        }
    }

    usingT
    T &my_vector<T>::operator[](std::size_t index) const {
        if (index >= size_)
            throw std::exception();
        return array_[index];
    }

    usingT
    void my_vector<T>::push_back(const T &t) {
        reserve(size_ + 1);
        new(array_ + size_)T(t);
        size_++;
    }

    usingT
    void my_vector<T>::pop_back() {
        resize(--size_);
    }

    usingT
    void my_vector<T>::clear() {
        resize(0);
    }

}