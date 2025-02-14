#include "s21_cat.h"

int main(int argn, char *argv[]) {
  int counter = 1;
  int string_counter = 1;
  int n_flag = 0;
  struct options opt = {0, 0, 0, 0, 0, 0, 0};

  while (counter < argn) {
    if (argv[counter][0] == '-') {
      arg_checker(argv[counter], &opt);
    }

    counter++;
  }
  if (opt.is_false) {
    fprintf(stderr, "n/a\n");
  }

  for (int i = 1; i < argn; i++) {
    if (argv[i][0] != '-') {
      if (n_flag == 1) {
        printf("\n");
      }
      read_txt(argv[i], opt, &string_counter);

      n_flag = 1;
    }
  }
  return 0;
}

int arg_checker(char *arg, struct options *opt) {
  if ((!strcmp(arg, "-b")) || (!strcmp(arg, "--number-nonblank"))) {
    opt->b = 1;
  } else if ((!strcmp(arg, "-e"))) {
    opt->e = 1;
    opt->v = 1;
  } else if ((!strcmp(arg, "-v"))) {
    opt->v = 1;
  } else if ((!strcmp(arg, "-n")) || (!strcmp(arg, "--number"))) {
    opt->n = 1;
  } else if ((!strcmp(arg, "-s")) || (!strcmp(arg, "--squeeze-blank"))) {
    opt->s = 1;
  } else if ((!strcmp(arg, "-t"))) {
    opt->t = 1;
    opt->v = 1;
  } else if ((!strcmp(arg, "-E"))) {
    opt->e = 1;
  } else if ((!strcmp(arg, "-T"))) {
    opt->t = 1;
  } else {
    opt->is_false = 1;
  }

  return 0;
}

int read_txt(char *txt_name, struct options opt, int *string_counter) {
  int ex_code = 1;
  int emptyprinted = 0;
  int is_string_empty = 0;
  int is_first = 1;
  FILE *pfile = fopen(txt_name, "r");
  char row[256];

  if (pfile != NULL) {
    while (fgets(row, 256, pfile) != NULL) {
      print_str(row, opt, &is_first, &is_string_empty, string_counter,
                &emptyprinted);
      is_first = 0;
    }
    fclose(pfile);
  } else {
    ex_code = 0;
  }

  return ex_code;
}

int printe(int is) {
  if (is == 1) {
    printf("$");
  }
  return 0;
}

int transfer(int *is_first, struct options opt, int is_empty,
             int *emptyprinted) {
  if (*is_first) {
    *is_first = 0;
  } else {
    if (is_empty == 1) {
      printe(opt.e);
      printf("\n");
      *emptyprinted = 0;
    } else if (is_empty == 0 && *emptyprinted == 0) {
      printe(opt.e);
      printf("\n");
      *emptyprinted = 1;
    } else if (is_empty == 1 && *emptyprinted == 1) {
      *emptyprinted = 0;
    }
  }
  return 0;
}

int print_str(char *row, struct options opt, int *is_first, int *is_empty,
              int *string_counter, int *emptyprinted) {
  int ex_code = 1;
  if (row[0] == '\n') {
    *is_empty = 0;
  } else {
    *is_empty = 1;
  }
  if (opt.s == 1) {
    transfer(is_first, opt, *is_empty, emptyprinted);
  } else if (*is_first == 0) {
    printe(opt.e);
    printf("\n");
  }
  if (!(opt.s == 1 && row[0] == '\n' && *is_empty == 1)) {
    if (opt.b == 1) {
      if (row[0] != '\n') {
        printf("%6d\t", *string_counter);
        *string_counter = *string_counter + 1;
      }
    } else if (opt.n == 1) {
      printf("%6d\t", *string_counter);
      *string_counter = *string_counter + 1;
    }
    for (size_t i = 0; i < strlen(row); i++) {
      if (opt.t == 1 && row[i] == '\t') {
        printf("^I");
      } else if (row[i] != '\n') {
        print_chr(row[i], opt);
      }
    }
  }
  return ex_code;
}

int print_chr(char row, struct options opt) {
  int i = (int)row;

  if (i < 0) {
    i = 256 + i;
  }
  if (opt.v == 1) {
    if (i < 32) {
      printf("^%c", i + 64);
    } else if (i > 126) {
      if (i != 127) {
        printf("M-");
      }

      if (i > 159) {
        i = i - 64;
      } else {
        printf("^");
      }
      if (i == 191) {
        i = i - 64;
        printf("^");
      }
      printf("%c", i - 64);
    } else {
      printf("%c", row);
    }
  } else {
    printf("%c", row);
  }
  return 0;
}