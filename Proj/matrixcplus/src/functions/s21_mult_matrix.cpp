#include "../s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix &other) {
  S21Matrix result(rows_, other.cols_);
  if (cols_ != other.rows_) {
    throw std::length_error("err");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        for (int k = 0; k < this->cols_; k++)
          result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
    *this = result;
  }
}
