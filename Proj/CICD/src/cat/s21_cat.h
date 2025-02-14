#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <string.h>

struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int is_false;
};

int arg_checker(char *arg, struct options *opt);
int read_txt(char *txt_name, struct options opt, int *string_counter);
int printe(int is);
int transfer(int *is_first, struct options opt, int is_empty,
             int *emptyprinted);
int print_str(char *row, struct options opt, int *is_first, int *count,
              int *is_empty, int *emptyprinted);
int print_chr(char row, struct options opt);

#endif