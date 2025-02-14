#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool ex_code = true;

  if (this->matrix_ != nullptr && other.matrix_ != nullptr && this->rows_ > 0 &&
      other.rows_ > 0 && this->cols_ > 0 && other.cols_ > 0 &&
      this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          ex_code = false;
        }
      }
    }
  } else {
    ex_code = false;
  }

  return ex_code;
}
