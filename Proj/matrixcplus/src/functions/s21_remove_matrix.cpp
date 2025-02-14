#include "../s21_matrix_oop.h"

void S21Matrix::removeMatrix() {
  for (int i = (rows_ - 1); i >= 0; i--) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}
