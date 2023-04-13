#include "matrix.h"
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

void Matrix::DeleteMatrix() {
    for (size_t i = 0; i < _rows; i++)
        delete[] _data[i];
    delete[]_data;
}

Matrix::~Matrix() {
    DeleteMatrix();
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this == &matrix)
        return *this;
    DeleteMatrix();
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

Matrix Matrix::operator+(const Matrix &m) const {
    if (_rows != m._rows || _cols != m._cols)
        throw std::runtime_error("Invalid sizes");

    Matrix tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            tmp._data[i][j] = _data[i][j] + m._data[i][j];

    return tmp;
}

Matrix Matrix::operator-(const Matrix &m) const {
    if (_rows != m._rows || _cols != m._cols)
        throw std::runtime_error("Invalid sizes");

    Matrix tmp = Matrix(_rows, _cols);

    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            tmp._data[i][j] = _data[i][j] - m._data[i][j];

    return tmp;
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (_cols != m._rows)
        throw std::runtime_error("Invalid sizes");

    Matrix tmp = Matrix(_rows, m._cols);

    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < m._cols; j++) {
            for (size_t k = 0; k < _cols; k++)
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
        }

    return tmp;
}

Matrix &Matrix::operator+=(const Matrix &m) {
    *this = (*this) + m;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
    *this = (*this) - m;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    *this = (*this) * m;
    return *this;
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

void Matrix::print(FILE *f) const {
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            if (j != _cols - 1)
                fprintf(f, "%d ", _data[i][j]);
            else
                fprintf(f, "%d", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}