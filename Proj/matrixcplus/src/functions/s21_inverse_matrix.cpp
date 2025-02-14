#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (!determinant) {
    throw std::length_error("err");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ > 1) {
    result = this->CalcComplements().Transpose() * (1.0 / determinant);
  } else
    result.matrix_[0][0] = 1.0 / determinant;
  return result;
}
