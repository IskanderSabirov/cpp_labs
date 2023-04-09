#include "matrix.h"

namespace my_matrix {
    Matrix::Matrix() : rows_(0) {
        cols_ = 0;
        try {
            data_ = new int *[0];
        } catch (std::bad_alloc &e) {
            throw my_exception::MatrixException("Unable to allocate memory.");
        }
    }

    Matrix::Matrix(size_t r, size_t c) : rows_(0), cols_(0) {
        try {
            data_ = new int *[r];
            for (size_t i = 0; i < r; i++) {
                data_[i] = new int[cols_];
                cols_ = c;
                rows_++;
            }
        } catch (std::bad_alloc &e) {
            throw my_exception::MatrixException("Unable to allocate memory.");
        }

        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                data_[i][j] = 0;
    }

    Matrix::Matrix(const Matrix &matrix) : rows_(0), cols_(0) {
        try {
            data_ = new int *[matrix.rows_];
            for (size_t i = 0; i < matrix.rows_; i++) {
                data_[i] = new int[cols_];
                cols_ = matrix.cols_;
                rows_++;
            }
        } catch (std::bad_alloc &e) {
            throw my_exception::MatrixException("Unable to allocate memory.");
        }

        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                data_[i][j] = matrix.data_[i][j];
    }

    void Matrix::DeleteMatrix() {
        for (size_t i = 0; i < rows_; i++)
            delete[] data_[i];
        delete[]data_;
    }

    Matrix::~Matrix() {
        DeleteMatrix();
    }

    Matrix &Matrix::operator=(const Matrix &matrix) {
        if (this == &matrix)
            return *this;

        try {
            auto t = new int *[matrix.rows_];
            DeleteMatrix();
            data_ = t;
            rows_ = 0;
            cols_ = 0;
            for (size_t i = 0; i < matrix.rows_; i++) {
                data_[i] = new int[cols_];
                cols_ = matrix.cols_;
                rows_++;
            }
        } catch (std::bad_alloc &e) {
            throw my_exception::MatrixException("Unable to allocate memory.");
        }

        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                data_[i][j] = matrix.data_[i][j];

        return *this;
    }

    [[maybe_unused]] size_t Matrix::get_rows() const {
        return rows_;
    }

    [[maybe_unused]] size_t Matrix::get_cols() const {
        return cols_;
    }

    void Matrix::set(size_t i, size_t j, int val) {
        if (i >= rows_ || j >= cols_)
            throw std::runtime_error("Invalid indices ");

        data_[i][j] = val;
    }

    int Matrix::get(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_)
            throw my_exception::MatrixException("ACCESS: bad index.");

        return data_[i][j];
    }

    Matrix Matrix::operator+(const Matrix &m) const {
        if (rows_ != m.rows_ || cols_ != m.cols_)
            throw my_exception::MatrixException("ADD: dimensions do not match.");

        Matrix tmp(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                tmp.data_[i][j] = data_[i][j] + m.data_[i][j];

        return tmp;
    }

    Matrix Matrix::operator-(const Matrix &m) const {
        if (rows_ != m.rows_ || cols_ != m.cols_)
            throw std::runtime_error("Invalid sizes");

        Matrix tmp = Matrix(rows_, cols_);

        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                tmp.data_[i][j] = data_[i][j] - m.data_[i][j];

        return tmp;
    }

    Matrix Matrix::operator*(const Matrix &m) const {
        if (cols_ != m.rows_)
            throw my_exception::MatrixException("MUL: #arg1.columns != #arg2.rows.");

        Matrix tmp = Matrix(rows_, m.cols_);


        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < m.cols_; j++) {
                for (size_t k = 0; k < cols_; k++)
                    tmp.data_[i][j] += data_[i][k] * m.data_[k][j];
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
        if (rows_ != m.rows_ || cols_ != m.cols_)
            return false;
        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                if (data_[i][j] != m.data_[i][j])
                    return false;
        return true;
    }

    bool Matrix::operator!=(const Matrix &m) const {
        return !((*this) == m);
    }

    void Matrix::print(std::ostream &ostream) const {
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                if (j != cols_ - 1)
                    ostream << data_[i][j] << " ";
                else
                    ostream << data_[i][j] << std::endl;
            }
        }
    }

    std::ostream &operator<<(std::ostream &ostream, Matrix &m) {
        m.print(ostream);
        return ostream;
    }
}