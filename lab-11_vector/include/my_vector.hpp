#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector &other);
    ~my_vector();

    std::size_t size();
    std::size_t capacity();
    bool empty();

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T operator[](std::size_t index);

    void push_back(T t);
    void pop_back();
    void clear();

    friend std::ostream &operator<<(std::ostream &ostream, const my_vector &v);

private:
    void destroy_vector();
    size_t capacity_;
    size_t size_;
    T* array_;
};

}

#endif  // MY_VECTOR_H_
