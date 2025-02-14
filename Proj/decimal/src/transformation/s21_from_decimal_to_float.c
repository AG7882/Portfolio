#include "./../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ex_code = 0;
  if (!dst) {
    // fprintf(stderr, "err\n");
    ex_code = 1;
  } else {
    double res = 0;
    float degree = 1;
    get_degree(src, &degree);

    res = src.bits[2] * powl(2, 64) + src.bits[1] * powl(2, 32) + src.bits[0];

    res = res / powl(10, degree);
    if (get_bit(src, 127) == 1) {
      res = -res;
    }

    *dst = (float)res;
  }
  return ex_code;
}