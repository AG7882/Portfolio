#include "./../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int ex_code = 0;
  if (!dst) {
    // fprintf(stderr, "err\n");
    ex_code = 1;
  } else {
    initial_num(dst);
    // initial_num(dst);
    int res = src;
    int counter = 0;
    ;
    if (src < 0) {
      set_sign(dst, 1);
    }

    while (res != 0)  // rep
    {
      set_bit(dst, counter, res % 2);
      res = res / 2;
      counter++;
    }
  }

  return ex_code;
}
