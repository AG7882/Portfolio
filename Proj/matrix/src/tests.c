#include <check.h>

#include "s21_matrix.h"

START_TEST(create1) {
  matrix_t A;
  int rows = 1;
  int columns = -1;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create2) {
  matrix_t A;
  int rows = 0;
  int columns = 1;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create3) {
  int rows = 10;
  int columns = 10;
  int res = s21_create_matrix(rows, columns, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create4) {
  matrix_t A;
  int rows = 10;
  int columns = 10;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(remove1) {
  matrix_t A;
  s21_create_matrix(10, 10, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_eq(A.matrix, NULL);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(equal1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal2) {
  matrix_t A;
  matrix_t B;
  double A_mass[4] = {1.1, 2.2, 3.3333333, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 0.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal3) {
  matrix_t A;
  matrix_t B;
  double A_mass[4] = {1.1, 2.2, 3.3333333, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 1.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 1.0};
  double C_mass[4] = {2.2, -0.1, 6.6666666, 1.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  add_numbers(C_mass, &C);
  int res = s21_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sum2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 1.0};
  double C_mass[4] = {2.2, -0.1, 0.0, 1.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  add_numbers(C_mass, &C);
  int res = s21_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 0);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sum3) {
  int res = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sum4) {
  matrix_t A;
  matrix_t B;
  matrix_t D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  int res = s21_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {2.2, -0.1, 6.6666666, 1.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 1.0};
  double C_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  add_numbers(C_mass, &C);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sub2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3333333, 1.0};
  double C_mass[4] = {2.2, -0.1, 0.0, 1.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  add_numbers(C_mass, &C);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 0);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sub3) {
  int res = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub4) {
  matrix_t A;
  matrix_t B;
  matrix_t D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_n1) {
  matrix_t A;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  double B_num = 2.0;
  double C_mass[4] = {2.2, -4.6, 6.6666666, 0.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(C_mass, &C);
  int res = s21_mult_number(&A, B_num, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(mult_n2) {
  matrix_t A;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  s21_create_matrix(2, 2, &A);
  add_numbers(A_mass, &A);
  int res = s21_mult_number(&A, NAN, &D);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_n3) {
  matrix_t A;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3333333, 0.0};
  double B_num = 2.0;
  s21_create_matrix(2, 2, &A);
  add_numbers(A_mass, &A);
  int res = s21_mult_number(NULL, B_num, &D);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_m1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3, 1.0};
  double C_mass[4] = {-6.38, 0.12, 3.63, 7.26};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  add_numbers(C_mass, &C);
  int res = s21_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(mult_m2) {
  int res = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mult_m3) {
  matrix_t A;
  matrix_t B;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3, 0.0};
  double B_mass[4] = {1.1, 2.2, 3.3, 1.0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(3, 4, &B);
  add_numbers(A_mass, &A);
  add_numbers(B_mass, &B);
  int res = s21_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transpose1) {
  matrix_t A;
  matrix_t C;
  matrix_t D;
  double A_mass[4] = {1.1, -2.3, 3.3, 0.0};
  double C_mass[4] = {1.1, 3.3, -2.3, 0.0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &C);
  add_numbers(A_mass, &A);
  add_numbers(C_mass, &C);
  int res = s21_transpose(&A, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(transpose2) {
  int res = s21_transpose(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(determinant1) {
  matrix_t A;
  double determinant = 0;
  double A_mass[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21_create_matrix(3, 3, &A);
  add_numbers(A_mass, &A);
  int res = s21_determinant(&A, &determinant);
  ck_assert_double_eq(determinant, 0);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant2) {
  int res = s21_determinant(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(determinant3) {
  matrix_t A;
  double determinant = 0;
  s21_create_matrix(3, 2, &A);
  int res = s21_determinant(&A, &determinant);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_mass[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double C_mass[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  add_numbers(A_mass, &A);
  add_numbers(C_mass, &C);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(calc2) {
  int res = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(calc3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_mass[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double C_mass[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  add_numbers(A_mass, &A);
  add_numbers(C_mass, &C);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_double_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse2) {
  int res = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(inverse3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tcase_creat = tcase_create("CREATE");
  tcase_add_test(tcase_creat, create1);
  tcase_add_test(tcase_creat, create2);
  tcase_add_test(tcase_creat, create3);
  tcase_add_test(tcase_creat, create4);
  suite_add_tcase(suite, tcase_creat);

  TCase *tcase_remove = tcase_create("REMOVE");
  tcase_add_test(tcase_remove, remove1);
  suite_add_tcase(suite, tcase_remove);

  TCase *tcase_equal = tcase_create("EQUAL");
  tcase_add_test(tcase_equal, equal1);
  tcase_add_test(tcase_equal, equal2);
  tcase_add_test(tcase_equal, equal3);
  tcase_add_test(tcase_equal, equal4);
  suite_add_tcase(suite, tcase_equal);

  TCase *tcase_sum = tcase_create("SUM");
  tcase_add_test(tcase_sum, sum1);
  tcase_add_test(tcase_sum, sum2);
  tcase_add_test(tcase_sum, sum3);
  tcase_add_test(tcase_sum, sum4);
  suite_add_tcase(suite, tcase_sum);

  TCase *tcase_sub = tcase_create("SUB");
  tcase_add_test(tcase_sub, sub1);
  tcase_add_test(tcase_sub, sub2);
  tcase_add_test(tcase_sub, sub3);
  tcase_add_test(tcase_sub, sub4);
  suite_add_tcase(suite, tcase_sub);

  TCase *tcase_multi_num = tcase_create("MULTI_NUM");
  tcase_add_test(tcase_multi_num, mult_n1);
  tcase_add_test(tcase_multi_num, mult_n2);
  tcase_add_test(tcase_multi_num, mult_n3);
  suite_add_tcase(suite, tcase_multi_num);

  TCase *tcase_multi_mat = tcase_create("MULTI_MAT");
  tcase_add_test(tcase_multi_mat, mult_m1);
  tcase_add_test(tcase_multi_mat, mult_m2);
  tcase_add_test(tcase_multi_mat, mult_m3);
  suite_add_tcase(suite, tcase_multi_mat);

  TCase *tcase_transpose = tcase_create("TRANSPOSE");
  tcase_add_test(tcase_transpose, transpose1);
  tcase_add_test(tcase_transpose, transpose2);
  suite_add_tcase(suite, tcase_transpose);

  TCase *tcase_deter = tcase_create("DETERMINANT");
  tcase_add_test(tcase_deter, determinant1);
  tcase_add_test(tcase_deter, determinant2);
  tcase_add_test(tcase_deter, determinant3);
  suite_add_tcase(suite, tcase_deter);

  TCase *tcase_calc = tcase_create("CALC");
  tcase_add_test(tcase_calc, calc1);
  tcase_add_test(tcase_calc, calc2);
  tcase_add_test(tcase_calc, calc3);
  suite_add_tcase(suite, tcase_calc);

  TCase *tcase_inverse = tcase_create("INVERSE");
  tcase_add_test(tcase_inverse, inverse1);
  tcase_add_test(tcase_inverse, inverse2);
  tcase_add_test(tcase_inverse, inverse3);
  suite_add_tcase(suite, tcase_inverse);
  return suite;
}

int main() {
  int count = 0;
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
