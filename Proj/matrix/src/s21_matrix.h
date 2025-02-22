#ifndef S21_MATRIX
#define S21_MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EX_CODE_OK 0
#define EX_CODE_WRONG_MATRIX 1
#define EX_CODE_CALC_ERR 2
#define ZERO_FOR_DOUBLE 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);

double s21_get_determinant(matrix_t *A);
int s21_get_minor(matrix_t *A, int row, int column, matrix_t *B);
void add_numbers(double *nums, matrix_t *A);

#endif