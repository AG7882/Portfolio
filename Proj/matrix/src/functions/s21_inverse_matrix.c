#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double determinant = 0;
  int ex_code = EX_CODE_OK;
  if (A == NULL || A->columns <= 0 || A->rows <= 0 || result == NULL) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (A->columns != A->rows || s21_determinant(A, &determinant) ||
             fabs(determinant) <= ZERO_FOR_DOUBLE) {
    ex_code = EX_CODE_CALC_ERR;
  } else if (A->rows == 1) {
    if (!s21_create_matrix(1, 1, result))
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    else
      ex_code = EX_CODE_WRONG_MATRIX;
  } else {
    matrix_t calc_c;
    ex_code = s21_calc_complements(A, &calc_c);
    if (!ex_code) {
      matrix_t trans_matrix;
      s21_transpose(&calc_c, &trans_matrix);
      s21_mult_number(&trans_matrix, 1.0 / determinant, result);
      s21_remove_matrix(&calc_c);
      s21_remove_matrix(&trans_matrix);
    }
  }
  return ex_code;
}