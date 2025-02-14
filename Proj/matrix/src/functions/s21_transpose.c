#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ex_code = EX_CODE_OK;

  if (A == NULL || result == NULL) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else {
    ex_code = s21_create_matrix(A->columns, A->rows, result);
    if (!ex_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      ex_code = EX_CODE_WRONG_MATRIX;
    }
  }
  return ex_code;
}