#include "../s21_matrix_oop.h"

double S21Matrix::Determinant() {
  double result = 0;
  if (this->cols_ != this->rows_) {
    throw std::length_error("err");
  } else if (this->rows_ == 1) {
    result = this->matrix_[0][0];
  } else {
    result = get_determinant();
  }
  return result;
}

double S21Matrix::get_determinant() {
  double result = 0;
  if (this->rows_ == 2 && this->cols_ == 2) {
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[0][1] * this->matrix_[1][0];
  } else {
    for (int i = 0; i < this->rows_; i++) {
      S21Matrix minor = get_minor(0, i);
      result += pow(-1, i) * this->matrix_[0][i] * minor.get_determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::get_minor(int row, int column) const {
  S21Matrix result(rows_ - 1, cols_ - 1);

  int i_index = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      int j_index = 0;
      for (int j = 0; j < cols_; j++)
        if (j != column) {
          result.matrix_[i_index][j_index] = this->matrix_[i][j];
          j_index++;
        }
      i_index++;
    }
  }

  return result;
}
