#include "./../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ex_code = 0;
  char src_copy[256] = "";
  int sequence = 0;
  int backward_length = 0;

  if (!dst || (fabs(src) > 0 && fabs(src) < 1e-28) ||
      (fabs(src) - 79228162514264337593543950335.0 > 0) || isinf(src)) {
    // fprintf(stderr, "err\n");
    ex_code = 1;
  } else {
    initial_num(dst);
    // dst->bits[3] = 0;
    sprintf(src_copy, "%E", fabs(src));

    backward_length = 0;
    int n = 7;
    while (n > 1 && src_copy[n] == '0') {
      backward_length++;
      n--;
    }
    sequence = get_sequense(src_copy);
    // printf("-%d-\n", sequence);
    // s21_from_int_to_decimal(sequence, dst);
    dst->bits[0] = sequence / pow(10, backward_length);

    s21_from_float_to_decimal_set_degree(backward_length, dst, src_copy);

    if (src < 0) {
      set_sign(dst, 1);
    }
  }
  // print_decimal(*dst);
  return ex_code;
}

int s21_from_float_to_decimal_set_degree(int backward_length,

                                         s21_decimal *dst, char src_copy[256]) {
  int degree = 0;
  int n = 10;
  /*if (src_copy[0] == '-') {
    n++;
  }
*/
  for (int i = n; i < (int)strlen(src_copy); i++) {
    degree = degree + (src_copy[i] - '0') * pow(10, strlen(src_copy) - 1 - i);
  }
  if (src_copy[9] == '-') {
    degree = -degree;
  }

  degree = 6 - backward_length - degree;
  s21_decimal multiplier = {{10, 0, 0, 0}};
  if (degree < 0) {
    while (degree != 0) {
      s21_mul(*dst, multiplier, dst);
      degree++;
    }
  }

  // printf("1=%c\n", src_copy[10]);
  // printf("1=%c\n", src_copy[11]);
  // printf("d=%d\n", degree);
  set_degree(dst, degree);

  return 0;
}