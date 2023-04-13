#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    private:

        std::size_t size_ = N;

        T data_[N];

    public:

        my_array() = default;

        my_array(const my_array &t) {
            for (size_t i = 0; i < N; ++i)
                data_[i] = t.data_[i];
        }

        const T &at(std::size_t index) const {
            if (index >= N)
                throw std::out_of_range("Invalid index ");
            return data_[index];
        }

        T &at(std::size_t index) {
            if (index >= N)
                throw std::out_of_range("Invalid index ");
            return data_[index];
        }

        const T &operator[](std::size_t index) const {
            return data_[index];
        }

        T &operator[](std::size_t index) {
            return data_[index];
        }


        bool empty() const {
            return size_ == 0;
        }

        std::size_t size() const {
            return size_;
        }

        void fill(T val) {
            for (size_t i = 0; i < N; ++i)
                data_[i] = val;
        }

    };

    template<size_t N>
    class my_array<bool, N> {
    private:
        static const size_t _bucketSize = 8;
        uint8_t _data[(N + _bucketSize - 1) / _bucketSize] = {};

        class proxy {
        private:
            uint8_t &_storage;
            uint8_t _pos;
        public:
            proxy(uint8_t &storage, uint8_t pos) : _storage(storage), _pos(pos) {}

            operator bool() const {
                return _storage >> _pos & 1;
            }

            proxy &operator=(bool new_value) {
                _storage &= uint8_t(-1) ^ (1 << _pos);
                _storage |= new_value << _pos;
                return *this;
            }

            proxy &operator=(const proxy &other_proxy) {
                return operator=(bool(other_proxy));
            }
        };

    public:
        my_array() = default;

        my_array(const my_array &other_array) {
            std::copy(std::begin(other_array._data), std::end(other_array._data), _data);
        }

        bool operator[](size_t index) const {
            return _data[index / _bucketSize] >> (index % _bucketSize) & 1;
        }

        proxy operator[](size_t index) {
            return proxy(_data[index / _bucketSize], index % _bucketSize);
        }

        bool at(size_t index) const {
            if (index >= N)
                throw std::out_of_range("Array index out of range");
            return operator[](index);
        }

        proxy at(size_t index) {
            if (index >= N)
                throw std::out_of_range("Array index out of range");
            return operator[](index);
        }

        bool empty() const {
            return N == 0;
        }

        bool size() const {
            return N;
        }

        void fill(bool new_value) {
            if (new_value)
                std::fill(std::begin(_data), std::end(_data), uint8_t(-1));
            else
                std::fill(std::begin(_data), std::end(_data), uint8_t(0));
        }
    };
}