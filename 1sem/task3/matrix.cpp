#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <iostream>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, uint64_t Rows, uint64_t Cols>
class Matrix {
 public:
  T matrix_[Rows][Cols];
  uint64_t RowsNumber() const {
    return Rows;
  }

  uint64_t ColumnsNumber() const {
    return Cols;
  }

  T operator()(uint64_t i, uint64_t j) const {
    return matrix_[i][j];
  }

  T& operator()(uint64_t i, uint64_t j) {
    return matrix_[i][j];
  }

  T At(uint64_t i, uint64_t j) const {
    if (i > Rows || j > Cols) {
      throw MatrixOutOfRange{};
    }
    return matrix_[i][j];
  }

  T& At(uint64_t i, uint64_t j) {
    if (i > Rows || j > Cols) {
      throw MatrixOutOfRange{};
    }
    return matrix_[i][j];
  }

  Matrix& operator+=(const Matrix& other) {
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        matrix_[i][j] += other(i, j);
      }
    }
    return *this;
  }

  Matrix& operator-=(const Matrix& other) {
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        matrix_[i][j] -= other(i, j);
      }
    }
    return *this;
  }

  Matrix& operator*=(T val) {
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        At(i, j) *= val;
      }
    }
    return *this;
  }

  Matrix operator*(T val) const {
    Matrix<T, Rows, Cols> new_matrix;
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        new_matrix(i, j) = At(i, j) * val;
      }
    }
    return new_matrix;
  }

  Matrix operator/(T val) const {
    Matrix<T, Rows, Cols> new_matrix;
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        new_matrix(i, j) = At(i, j) / val;
      }
    }
    return new_matrix;
  }

  Matrix& operator/=(T val) {
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        At(i, j) /= val;
      }
    }
    return *this;
  }

  template <typename T1>
  friend std::istream& operator>>(std::istream& in, Matrix<T, Rows, Cols>&);

  bool operator==(const Matrix& b) const {
    for (uint64_t i = 0; i < Rows; i++) {
      for (uint64_t j = 0; j < Cols; j++) {
        if (At(i, j) != b(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix& b) const {
    return !(*this == b);
  }

  friend const Matrix<T, Rows, Cols> operator*(T p, const Matrix<T, Rows, Cols>& a) {
    return a * p;
  }
};

template <class T, uint64_t Rows, uint64_t Cols>
Matrix<T, Cols, Rows> GetTransposed(const Matrix<T, Rows, Cols>& a) {
  Matrix<T, Cols, Rows> new_matrix;
  for (uint64_t i = 0; i < Cols; i++) {
    for (uint64_t j = 0; j < Rows; j++) {
      new_matrix(i, j) = a(j, i);
    }
  }
  return new_matrix;
}

template <class T, uint64_t Rows, uint64_t Cols>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Rows, Cols>& a) {
  for (uint64_t i = 0; i < Rows; i++) {
    for (uint64_t j = 0; j < Cols; j++) {
      out << a(i, j);
      if (j != Cols - 1) {
        out << " ";
      }
    }
    out << '\n';
  }
  return out;
}

template <class T, uint64_t Rows, uint64_t Cols>
std::istream& operator>>(std::istream& in, Matrix<T, Rows, Cols>& a) {
  for (uint64_t i = 0; i < Rows; i++) {
    for (uint64_t j = 0; j < Cols; j++) {
      in >> a(i, j);
    }
  }
  return in;
}

template <class T, uint64_t Rows, uint64_t Cols, uint64_t Cols1>
T Scalar(const Matrix<T, Rows, Cols>& a, const Matrix<T, Cols, Cols1>& b, uint64_t pos_i, uint64_t pos_j) {
  T result = 0;
  for (uint64_t i = 0; i < Cols; i++) {
    result += a(pos_i, i) * b(i, pos_j);
  }
  return result;
}

template <class T, uint64_t Rows, uint64_t Cols, uint64_t Cols1>
const Matrix<T, Rows, Cols1> operator*(const Matrix<T, Rows, Cols>& a, const Matrix<T, Cols, Cols1>& b) {
  Matrix<T, Rows, Cols1> new_matrix;
  for (uint64_t i = 0; i < Rows; i++) {
    for (uint64_t j = 0; j < Cols1; j++) {
      new_matrix(i, j) = Scalar(a, b, i, j);
    }
  }
  return new_matrix;
}

template <class T, uint64_t Rows, uint64_t Cols>
Matrix<T, Rows, Cols>& operator*=(Matrix<T, Rows, Cols>& a, const Matrix<T, Cols, Cols>& b) {
  Matrix<T, Rows, Cols> new_matrix;
  new_matrix = a * b;
  for (uint64_t i = 0; i < Rows; i++) {
    for (uint64_t j = 0; j < Cols; j++) {
      a(i, j) = new_matrix(i, j);
    }
  }
  return a;
}

template <class T, uint64_t Rows, uint64_t Cols>
const Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& other) {
  Matrix<T, Rows, Cols> new_matrix = a;
  new_matrix += other;
  return new_matrix;
}

template <class T, uint64_t Rows, uint64_t Cols>
const Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& other) {
  Matrix<T, Rows, Cols> new_matrix = a;
  new_matrix -= other;
  return new_matrix;
}

#endif
