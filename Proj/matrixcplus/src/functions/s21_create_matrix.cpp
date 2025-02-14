#include "../s21_matrix_oop.h"

bool S21Matrix::createMatrix() {
  bool ex_code = EX_CODE_OK;
  matrix_ = new double *[rows_]();
  if (matrix_) {
    for (int i = 0; i < rows_ && !ex_code; i++) {
      matrix_[i] = new double[cols_]();
      if (!matrix_[i]) ex_code = EX_CODE_WRONG_MATRIX;
    }
    if (ex_code) {
      removeMatrix();
    }
  } else {
    ex_code = EX_CODE_WRONG_MATRIX;
  }
  return ex_code;
}
