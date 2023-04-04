#include "my_vector.hpp"

MyVector::MyVector() {
    _data = new int[2];
    _capacity = 2;
    _size = 0;
}

MyVector::MyVector(const MyVector &vector) {
    _size = vector._size;
    _capacity = vector._capacity;
    _data = new int[_capacity];
    for (std::size_t i = 0; i < _size; i++)
        _data[i] = vector._data[i];
}

void MyVector::operator=(const MyVector &vector) {

    if (&vector == this)
        return;

    delete[] _data;
    _size = vector._size;
    _capacity = vector._capacity;
    _data = new int[_capacity];

    for (std::size_t i = 0; i < _size; i++)
        _data[i] = vector._data[i];
}

[[maybe_unused]] MyVector::MyVector(std::size_t init_capacity) {
    _data = new int[init_capacity];
    _capacity = init_capacity;
    _size = 0;
}

MyVector::~MyVector() {
    delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
    if (index >= _size)
        throw std::runtime_error("Invalid index");

    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    if (index >= _size)
        throw std::runtime_error("Invalid index");

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

    for (size_t i = 0; i < _size; i++)
        t[i] = _data[i];

    delete[] _data;
    _data = t;
    _capacity = new_capacity;
}

void MyVector::resize(std::size_t new_size) {

    if (new_size < _capacity) {
        _size = new_size;
        return;
    }

    std::size_t max_capacity = (_capacity * 2 > new_size) ? _capacity * 2 : new_size;

    int *t = new int[max_capacity];

    for (size_t i = 0; i < max_capacity; i++)
        t[i] = (i < _size) ? _data[i] : 0;

    delete[] _data;
    _data = t;
    _capacity = max_capacity;
    _size = _capacity;
}

void MyVector::push_back(int value) {
    if (_size == _capacity) {
        int *t = new int[_capacity * 2];

        for (size_t i = 0; i < _capacity * 2; i++)
            t[i] = (i < _capacity) ? _data[i] : 0;

        delete[] _data;
        _data = t;
        _capacity *= 2;
    }

    _data[_size] = value;
    _size++;
}

void MyVector::insert(std::size_t index, int value) {

    if (index > _size)
        throw std::runtime_error("Invalid index");

    if (_size == _capacity)
        reserve(_capacity * 2);

    for (std::size_t i = _size; i > index; i--)
        _data[i] = _data[i - 1];

    _size++;
    _data[index] = value;
}

void MyVector::erase(std::size_t index) {

    if (index >= _size)
        throw std::runtime_error("Invalid index");

    for (std::size_t i = index; i < _capacity - 1; i++) {
        _data[i] = _data[i + 1];
    }

    _size--;
}
