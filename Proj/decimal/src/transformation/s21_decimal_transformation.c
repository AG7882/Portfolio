#include "./../s21_decimal.h"

// int get_decimal_to_int(s21_decimal src, int *dst) {
//   int counter = 0;
//   int res = get_bit(src, 0);
//   ;
//   for (int i = 1; i < 96; i++)  // rep
//   {
//     if (get_bit(src, i) == 1) {
//       res = res + pow(2, i);
//     }

//     counter++;
//   }
//   if (get_bit(src, 127) == 1) {
//     res = res * -1;
//   }

//   *dst = res;

//   return 0;
// }

int get_sequense(char *mass) {
  char res_char[7];
  int res = 0;
  int index = 0;
  /* for(int k = 0; k < 7; k++){
      res_char[k] = '0';
   }*/
  // printf("lsadsadasdasaddasd = %d\n", length);
  for (int i = 0; mass[i] < 'E'; i++) {
    if (mass[i] >= '0' && mass[i] <= '9') {
      res_char[index] = mass[i];
      index++;
    }
  }

  sscanf(res_char, "%d", &res);
  // printf("lsadsadasdasaddasd = %d|\n", res);
  /*int mult = 1;

  for (int t = length; t >= 0; t--)
  {
      if (mass[t] >= '0' && mass[t] <= '9')
      {
          res = res + (mass[t] - '0') * mult;
          mult = mult * 10;
      }
  }*/
  return res;
}

void get_degree(s21_decimal decimal, float *degree) {

  *degree = (decimal.bits[3] & 0x00ff0000) >> 16;
}
