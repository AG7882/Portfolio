#include "../s21_matrix.h"

void add_numbers(double *numbers, matrix_t *A) {
  int count = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = numbers[count];
      count++;
    }
  }
}
