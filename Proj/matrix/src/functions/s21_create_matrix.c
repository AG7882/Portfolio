#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ex_code = EX_CODE_OK;

  if (rows > 0 && columns > 0 && result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
  } else {
    ex_code = EX_CODE_WRONG_MATRIX;
  }
  return ex_code;
}
