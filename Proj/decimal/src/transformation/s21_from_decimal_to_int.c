#include "./../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ex_code = 0;
  int res = 0;
  s21_decimal copy;
  initial_num(&copy);
  ex_code = s21_truncate(src, &copy);
  if (!dst || ex_code == 1) {
    // fprintf(stderr, "err");
    ex_code = 1;
  } else {
    if (copy.bits[2] == 0 && copy.bits[1] == 0 && copy.bits[0] < 2147483648) {
      res = copy.bits[0];
      if (get_bit(src, 127) == 1) {
        res = -res;
      }
      *dst = res;
    } else {
      ex_code = 1;
    }
  }
  return ex_code;
}