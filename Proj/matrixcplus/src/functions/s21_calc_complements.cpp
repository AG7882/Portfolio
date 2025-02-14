#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::length_error("err");
  }
  S21Matrix result(rows_, cols_);
  if (this->rows_ == 1)
    result.matrix_[0][0] = this->matrix_[0][0];
  else {
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        S21Matrix minor = get_minor(i, j);
        double determinant = minor.Determinant();
        result.matrix_[i][j] = determinant * pow(-1, (double)(i + j));
        minor.~S21Matrix();
      }
    }
  }
  return result;
}
