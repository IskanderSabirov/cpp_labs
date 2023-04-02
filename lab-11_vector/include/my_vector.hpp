#ifndef LAB_11_VECTOR_MY_VECTOR_H
#define LAB_11_VECTOR_MY_VECTOR_H

#include <cstddef>
#include <iostream>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();

        [[maybe_unused]] explicit my_vector(std::size_t n);

        my_vector(const my_vector &other);

        my_vector &operator=(const my_vector &other);

        ~my_vector();

        [[nodiscard]] std::size_t size() const;

        [[nodiscard]] std::size_t capacity() const;

        [[nodiscard]] bool empty() const;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        T &operator[](std::size_t index) const;

        void push_back(const T &t);

        void pop_back();

        void clear();

        friend std::ostream &operator<<(std::ostream &ostream, my_vector &v) {
            for (size_t i = 0; i < v.size_; i++) {
                ostream << v[i];
                if (i != v.size_ - 1)
                    ostream << " ";
            }
            return ostream;
        }

    private:
        void destroy_vector();

        size_t calc_capacity(size_t n);

        size_t capacity_;
        size_t size_;
        T *array_;
    };

//    template<typename T>
//    std::ostream &operator<<(std::ostream &ostream, my_vector<T> &v) {
//        for (size_t i = 0; i < v.size_; i++) {
//            ostream << v[i];
//            if (i != v.size_ - 1)
//                ostream << " ";
//        }
//        return ostream;
//    }
}

#include "my_vector_impl.hpp"

#endif
