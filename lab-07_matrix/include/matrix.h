#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(size_t r, size_t c);
  Matrix(const Matrix& matrix);
  Matrix& operator=(const Matrix& matrix);
  ~Matrix();

  [[nodiscard]] size_t get_rows() const;
  [[nodiscard]] size_t get_cols() const;

  void set(size_t i, size_t j, int val);
  [[nodiscard]] int get(size_t i, size_t j) const;
  void print(FILE *f) const;

  Matrix operator+(Matrix& m) const;
  Matrix operator-(Matrix& m) const;
  Matrix operator*(Matrix& m) const;

  Matrix& operator+=(Matrix& m);
  Matrix& operator-=(Matrix& m);
  Matrix& operator*=(Matrix& m);

  bool operator==(Matrix& m) const;
  bool operator!=(Matrix& m) const;
private:
  size_t _rows;
  size_t _cols;
  int **_data;
};

#endif
