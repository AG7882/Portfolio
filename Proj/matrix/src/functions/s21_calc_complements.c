#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ex_code = EX_CODE_OK;
  if (A == NULL || A->columns <= 0 || A->rows <= 0 || result == NULL) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (A->columns != A->rows)
    ex_code = EX_CODE_CALC_ERR;
  else if (A->columns == 1) {
    ex_code = s21_create_matrix(1, 1, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    ex_code = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->columns && !ex_code; i++) {
      for (int j = 0; j < A->rows && !ex_code; j++) {
        matrix_t minor;
        ex_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        if (!ex_code) {
          s21_get_minor(A, i, j, &minor);
          double determinant = 0;
          s21_determinant(&minor, &determinant);
          result->matrix[i][j] = determinant * pow(-1, i + j);
        }
        s21_remove_matrix(&minor);
      }
    }
  }
  return ex_code;
}
