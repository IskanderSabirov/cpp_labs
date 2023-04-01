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

    T& operator[](std::size_t index) const;

    void push_back(const T& t);
    void pop_back();
    void clear();

    friend std::ostream& operator<<(std::ostream &ostream, my_vector& v){
        for(size_t i = 0 ; i < v.size_ ;i++ ){
            ostream << v[i];
            if(i!=v.size_-1)
                ostream << " ";
        }
        return ostream;
    }

private:
    void destroy_vector();
    size_t calc_capacity(size_t n);
    size_t capacity_;
    size_t size_;
    T* array_;
};

}

#endif  // MY_VECTOR_H_
