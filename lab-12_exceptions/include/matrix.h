#ifndef C_LABS_MATRIX_H
#define C_LABS_MATRIX_H

#include <cstdio>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "matrix_exception.h"

namespace my_matrix {
    class Matrix {
    public:
        Matrix();

        Matrix(size_t r, size_t c);

        Matrix(const Matrix &matrix);

        Matrix &operator=(const Matrix &matrix);

        ~Matrix();

        [[maybe_unused]] [[nodiscard]] size_t get_rows() const;

        [[maybe_unused]] [[nodiscard]] size_t get_cols() const;

        void set(size_t i, size_t j, int val);

        [[nodiscard]] int get(size_t i, size_t j) const;

        void print(std::ostream &ostream) const;

        Matrix operator+(const Matrix &m) const;

        Matrix operator-(const Matrix &m) const;

        Matrix operator*(const Matrix &m) const;

        Matrix &operator+=(const Matrix &m);

        Matrix &operator-=(const Matrix &m);

        Matrix &operator*=(const Matrix &m);

        bool operator==(const Matrix &m) const;

        bool operator!=(const Matrix &m) const;

        friend std::ostream &operator<<(std::ostream &ostream, Matrix &m);

    private:
        size_t rows_;
        size_t cols_;
        bool isData_;
        int **data_;
        void DeleteMatrix();
    };

}

#endif //C_LABS_MATRIX_H
