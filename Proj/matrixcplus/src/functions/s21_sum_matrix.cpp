#include "../s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!matrix_ || !other.matrix_ || rows_ != other.rows_ ||
      cols_ != other.cols_) {
    throw std::invalid_argument("err");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  }
}
