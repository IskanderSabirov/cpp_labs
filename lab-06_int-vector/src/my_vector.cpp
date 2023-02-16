#include "my_vector.hpp"
#include <memory>

MyVector::MyVector() {
    _data = new int[2];
    _capacity = 2;
    _size = 0;
}

[[maybe_unused]] MyVector::MyVector(std::size_t init_capacity) {
    _data = new int[init_capacity];
    _capacity = init_capacity;
    _size = 0;
}

MyVector::~MyVector() {
    delete[]_data;
}

void MyVector::set(std::size_t index, int value) {
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    return _data[index];
}

std::size_t MyVector::size() const {
    return _size;
}

std::size_t MyVector::capacity() const {
    return _capacity;
}

void MyVector::reserve(std::size_t new_capacity) {

    if (new_capacity <= _capacity)
        return;

    int *t = new int[new_capacity];

    for (size_t i = 0; i < new_capacity; i++) {
        if (i < _capacity) {
            t[i] = _data[i];
        } else {
            t[i] = 0;
        }
    }

    delete[] _data;
    _data = t;
    _capacity = new_capacity;
}

void MyVector::resize(std::size_t new_size) {

    if (new_size < _capacity)
        return;

    std::size_t max_capacity = (_capacity * 2 > new_size) ? _capacity * 2 : new_size;

    int *t = new int[max_capacity];

    for (size_t i = 0; i < max_capacity; i++) {
        if (i <= _size) {
            t[i] = _data[i];
        } else {
            t[i] = 0;
        }
    }

    delete[] _data;
    _data = t;
    _capacity = max_capacity;
}

void MyVector::push_back(int value) {
    if (_size == _capacity) {
        int *t = new int[_capacity * 2];

        for (size_t i = 0; i < _capacity * 2; i++) {
            if (i <= _capacity) {
                t[i] = _data[i];
            } else {
                t[i] = 0;
            }
        }

        delete[] _data;
        _data = t;
        _capacity *= 2;
    }

    _data[_size] = value;
    _size++;
}

void MyVector::insert(std::size_t index, int value) {

    if (_size == _capacity)
        reserve(_capacity * 2);

    for (std::size_t i = _size - 1; i > index; i++)
        _data[i] = _data[i - 1];

    _size++;
    _data[index] = value;
}

void MyVector::erase(std::size_t index) {

    int *t = new int[_capacity - 1];

    for (std::size_t i = 0; i < _capacity; i++) {
        if (i < index)
            t[i] = _data[i];
        if (i > index)
            t[i - 1] = _data[i];
    }

    delete[]_data;
    _data = t;
    _size--;
    _capacity++;
}
