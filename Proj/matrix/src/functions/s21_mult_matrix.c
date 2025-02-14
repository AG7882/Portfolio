#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ex_code = EX_CODE_OK;

  if (A == NULL || B == NULL || result == NULL || A->columns <= 0 ||
      A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (A->columns != B->rows) {
    ex_code = EX_CODE_CALC_ERR;
  } else {
    ex_code = s21_create_matrix(A->rows, B->columns, result);
    if (ex_code == 0)
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
  }
  return ex_code;
}