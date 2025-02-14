#include "./../s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int sign1 = get_bit(num1, 127);
  int sign2 = get_bit(num2, 127);
  int res = 1;
  int comp1 = 0;
  int comp2 = 0;
  if (sign1 != sign2) {
    res = 0;
  } else {
    for (int t = 0; t < 96; t++) {
      comp1 = get_bit(num1, t);
      comp2 = get_bit(num2, t);
      if (comp1 != comp2) {
        res = 0;
      }
    }
  }
  return res;
}