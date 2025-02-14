#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ex_code = EX_CODE_OK;

  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      B->rows <= 0 || A->columns <= 0 || B->columns <= 0) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    ex_code = EX_CODE_CALC_ERR;
  } else {
    ex_code = s21_create_matrix(A->rows, A->columns, result);
    if (!ex_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return ex_code;
}