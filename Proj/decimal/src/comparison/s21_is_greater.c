#include "./../s21_decimal.h"

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int sign1 = get_bit(num1, 127);
  int sign2 = get_bit(num2, 127);
  int res = 0;
  int comp1 = 0;
  int comp2 = 0;
  if (s21_is_equal(num1, num2) || sign1 > sign2) {
    res = 0;
  } else if (sign1 < sign2) {
    res = 1;
  } else {
    for (int t = 95; t >= 0; t--) {
      comp1 = get_bit(num1, t);
      comp2 = get_bit(num2, t);
      if ((comp1 > comp2 && sign1 == 0) ||
          (comp2 > comp1 &&
           sign1 == 1))  // если доходит до этой строки значит sign1 = sign2
      {
        res = 1;
        t = -1;
      } else if ((comp2 > comp1 && sign1 == 0) ||
                 (comp1 > comp2 && sign1 == 1)) {
        res = 0;
        t = -1;
      }
    }
  }
  return res;
}
