#include "matrix.hpp"
#include <iostream>

Matrix::Matrix(size_t r, size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];

    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] = 0;
}

Matrix::~Matrix() {
    DeleteMatrixData();
}

size_t Matrix::get_rows() const {
    return _rows;
}

size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
    if (i >= _rows || j >= _cols)
        throw std::runtime_error("Invalid indices ");

    _data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const {
    if (i >= _rows || j >= _cols)
        throw std::runtime_error("Invalid indices ");

    return _data[i][j];
}

bool Matrix::operator==(const Matrix &m) const {
    if (_rows != m._rows || _cols != m._cols)
        return false;
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            if (_data[i][j] != m._data[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !((*this) == m);
}

Matrix::Matrix(const Matrix &matrix) {
    _rows = matrix._rows;
    _cols = matrix._cols;
    _data = new int *[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] = matrix._data[i][j];
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this == &matrix)
        return *this;
    DeleteMatrixData();
    _rows = matrix._rows;
    _cols = matrix._cols;
    _data = new int *[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] = matrix._data[i][j];

    return *this;
}

void Matrix::DeleteMatrixData() {
    for (size_t i = 0; i < _rows; i++)
        delete[] _data[i];
    delete[]_data;
}


