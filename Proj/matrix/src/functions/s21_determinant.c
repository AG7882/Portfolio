#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int ex_code = EX_CODE_OK;
  if (A == NULL || A->columns <= 0 || A->rows <= 0 || result == NULL) {
    ex_code = EX_CODE_WRONG_MATRIX;
  } else if (A->columns != A->rows) {
    ex_code = EX_CODE_CALC_ERR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    *result = s21_get_determinant(A);
  }
  return ex_code;
}

double s21_get_determinant(matrix_t *A) {
  double result = 0;
  if (A->rows == 2 && A->columns == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

      s21_get_minor(A, 0, i, &minor);
      result += pow((-1), i) * A->matrix[0][i] * s21_get_determinant(&minor);
      s21_remove_matrix(&minor);
    }
  }
  return result;
}

int s21_get_minor(matrix_t *A, int row, int column, matrix_t *B) {
  int ex_code = EX_CODE_OK;
  int i_index = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      int j_index = 0;
      for (int j = 0; j < A->columns; j++)
        if (j != column) {
          B->matrix[i_index][j_index] = A->matrix[i][j];
          j_index++;
        }
      i_index++;
    }
  }

  return ex_code;
}
