#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ex_code = EX_CODE_OK;

  if (A == NULL || result == NULL || A->columns <= 0 || A->rows <= 0) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (isinf(number) || isnan(number)) {
    ex_code = EX_CODE_CALC_ERR;
  } else {
    ex_code = s21_create_matrix(A->rows, A->columns, result);
    if (!ex_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return ex_code;
}