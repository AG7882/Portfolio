#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argn, char *argv[]) {
  search(argv, argn);

  return 0;
}

int search(char **argv, int argn) {
  char args_e[256][256];
  int args_count = 0;
  char file_e[256][256];
  int file_count = 0;
  struct options opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 265; i++) {
    args_e[i][0] = '\0';
    file_e[i][0] = '\0';
  }

  options_filler(argn, &args_count, args_e, &file_count, file_e, argv, &opt);
  for (int i = 1; i < argn; i++) {
    if (argv[i][0] != '-' &&
        !(checklast(argv[i - 1], 'f', 'e') && argv[i - 1][0] == '-') &&
        !(checklast(argv[i - 1], 'e', 'f') && argv[i - 1][0] == '-')) {
      if (args_count == 0) {
        strcpy(args_e[args_count], argv[i]);
        args_count = args_count + 1;
      } else {
        strcpy(file_e[file_count], argv[i]);
        file_count = file_count + 1;
      }
    }
  }
  opt.txtcount = file_count;
  if (file_count == 0 || args_count == 0) {
    fprintf(stderr, "n/a\n");
  } else if (opt.err == 0) {
    for (int i = 0; i < file_count; i++) {
      open_file(file_e[i], &args_count, args_e, &opt);
    }
  }

  return 0;
}
int open_file(char *pos, int *args_count, char args_e[256][256],
              struct options *opt) {
  int ex_code = 1;
  opt->strcount = 0;
  FILE *pfile = fopen(pos, "r");
  opt->lprint = 0;
  if (pfile != NULL) {
    search_file(args_count, pos, args_e, pfile, opt);

    fclose(pfile);
  } else {
    ex_code = 0;
    if (!opt->s) {
      fprintf(stderr, "n/a\n");
    }
  }

  return ex_code;
}

int options_filler(int argn, int *args_count, char args_e[256][256],
                   int *file_count, char file_e[256][256], char **argv,
                   struct options *opt) {
  int chr;
  int index = 0;
  static struct option flags[] = {{0, 0, 0, 0}};
  while ((chr = getopt_long(argn, argv, "e:ivclnhsf:o", flags, &index)) != -1) {
    switch (chr) {
      case 'e':
        strcpy(args_e[*args_count], optarg);
        if (check(optarg, 'e')) {
          getopt_long(argn, argv, "e:ivclnhsf:o", flags, &index);
        }

        *args_count = *args_count + 1;
        opt->e = 1;
        break;
      case 'f':
        f_counter(optarg, args_count, args_e, opt);
        if (check(optarg, 'f')) {
          getopt_long(argn, argv, "e:ivclnhsf:o", flags, &index);
        }
        opt->f = 1;
        break;
      default:
        options_filler2nd(chr, index, file_count, file_e, argv, opt);

        break;
    }
  }

  return 0;
}

int options_filler2nd(char chr, int index, int *file_count,
                      char file_e[256][256], char **argv, struct options *opt) {
  switch (chr) {
    case 'i':
      opt->i = 1;
      break;
    case 'v':
      opt->v = 1;
      break;
    case 'c':
      opt->c = 1;
      break;
    case 'l':
      opt->l = 1;
      break;
    case 'n':
      opt->n = 1;
      break;
    case 'h':
      opt->h = 1;
      break;
    case 's':
      opt->s = 1;
      break;
    case 'o':
      opt->o = 1;
      break;
    default:

      if (argv[index][0] != '-') {
        strcpy(file_e[*file_count], argv[index]);
        *file_count = *file_count + 1;
      }
      break;
  }
  return 0;
}
int check(char *line, char chr) {
  int res = 0;
  for (unsigned int i = 0; i < strlen(line) - 1; i++) {
    if (chr == line[0]) {
      res = 1;
    }
  }

  return res;
}

int checklast(char *line, char chr, char chr2) {
  int res = 0;

  if (chr == line[strlen(line) - 1]) {
    res = 1;
    for (unsigned int i = 0; i < strlen(line) - 1; i++) {
      if (chr == line[i] || chr2 == line[i]) {
        res = 0;
      }
    }
  }

  return res;
}

int addarg(int i, unsigned int j, char **argv, char eorf, char args_e[256][256],
           int *args_count) {
  int res = 0;
  unsigned int cursor = 0;

  if (strlen(argv[i]) - 1 <= j) {
    res = 1;
  } else {
    while (cursor < strlen(args_e[i]) && args_e[i][cursor] != eorf) {
      cursor++;
    }
    char word[strlen(args_e[i]) - cursor];
    for (unsigned int z = 0; z < strlen(args_e[i]) - cursor; i++) {
      word[z] = args_e[i][cursor + z + 1];
    }
    strcpy(args_e[*args_count], word);
    *args_count = *args_count + 1;
  }
  return res;
}

int search_file(int *args_count, char *name, char args_e[256][256], FILE *pfile,
                struct options *opt) {
  int ex_code = 1;
  char row[4048];
  regex_t regex[*args_count];
  int regres;
  int snumber = 0;
  int regexcount = 0;
  int compresult = 0;
  int results = 0;
  for (int i = 0; i < *args_count; i++) {
    if (opt->i) {
      regres = regcomp(&regex[regexcount], args_e[i], REG_ICASE);
    } else {
      regres = regcomp(&regex[regexcount], args_e[i], 0);
    }
    if (regres) {
      fprintf(stderr, "regcomp err\n");
    } else {
      regexcount = regexcount + 1;
    }
  }
  while (fgets(row, 4048, pfile) != NULL) {
    snumber++;
    parse(*args_count, snumber, regexcount, &results, &compresult, row, name,
          args_e, regex, opt);
  }

  if (opt->c && !opt->l) {
    printname(name, opt);
    printf("%d\n", opt->strcount);
  }
  for (int i = 0; i < regexcount; i++) {
    regfree(&regex[i]);
  }
  return ex_code;
}

int parse(int args_count, int snumber, int regexcount, int *results,
          int *compresult, char *row, char *name, char args_e[256][256],
          regex_t *regex, struct options *opt) {
  int pos = 0;
  int length = 0;
  int forv = 0;
  char line[strlen(row)];
  regmatch_t mass[args_count];
  int is_found = 0;
  int is_in_row = 0;
  for (int i = 0; i < args_count; i++) {
    mass[i].rm_eo = 0;
    mass[i].rm_so = 0;
  }
  strcpy(line, row);
  parse2nd(&is_found, length, pos, &is_in_row, &forv, mass, snumber, regexcount,
           compresult, row, name, args_e, regex, opt);
  if (!opt->o && is_in_row == 1 && !opt->v) {
    print_all(snumber, line, name, opt);
  } else if (opt->v && is_in_row == 1 && !opt->o && forv == 0) {
    print_all(snumber, line, name, opt);
  }
  if ((is_in_row == 1) && (!opt->v || forv == 0)) {
    opt->strcount = opt->strcount + 1;
  }
  if (is_in_row == 1 && forv == 0) {
    *results = *results + 1;
  }
  return 0;
}

int parse2nd(int *is_found, int length, int pos, int *is_in_row, int *forv,
             regmatch_t *mass, int snumber, int regexcount, int *compresult,
             char *row, char *name, char args_e[256][256], regex_t *regex,
             struct options *opt) {
  for (unsigned int i = 0; i < strlen(row); i++) {
    *is_found = 0;
    length = 0;
    pos = strlen(row);
    for (int j = 0; j < regexcount; j++) {
      *compresult = regexec(&regex[j], row + i, 1, &mass[j], 0);
      if (*compresult == opt->v) {
        *is_found = 1;
        *is_in_row = 1;
      } else if (opt->v) {
        *forv = 1;
      }

      if (mass[j].rm_so < pos && !*compresult) {
        pos = mass[j].rm_so;
        length = strlen(args_e[j]);
      }
    }
    i = i + pos;
    if (length != 0) {
      forparse(*is_found, snumber, length, &i, name, row, opt);
    }
  }
  return 0;
}

int forparse(int is_found, int snumber, int length, unsigned int *i, char *name,
             char *row, struct options *opt) {
  if (is_found && !opt->c && !opt->l) {
    if (opt->o && !opt->v) {
      printname(name, opt);
      printnum(snumber, *opt);
      for (int j = 0; j < length; j++) {
        if (row[*i + j] != '\n') {
          printf("%c", row[*i + j]);
        }
      }
      printf("\n");
    }
  }
  if (opt->l && opt->lprint == 0 && is_found && !opt->v) {
    printname(name, opt);
    opt->lprint = 1;
    printf("\n");
  }
  return 0;
}

int print_all(int snumber, char *line, char *name, struct options *opt) {
  if (!opt->l) {
    if (!opt->c) {
      if (!opt->h) {
        printname(name, opt);
      }
      if (opt->n) {
        printnum(snumber, *opt);
      }
      del_n_symbol(line);
      printf("\n");
    }
  } else if (opt->lprint == 0) {
    printname(name, opt);
    printf("\n");
    opt->lprint = 1;
  }

  return 0;
}

int f_counter(char *optarg, int *argsn, char argsources[256][256],
              struct options *opt) {
  int ex_code = 0;
  char row[256];
  int flag = 0;
  int counter = 0;
  FILE *pfile = fopen(optarg, "r");
  if (pfile != NULL) {
    while (fgets(row, 256, pfile) != NULL && *argsn < 256) {
      counter = 0;
      flag = 0;
      for (unsigned int i = 0; i < strlen(row); i++) {
        if (row[i] == '\n' || row[i] == 10 || row[i] == '\0' || flag == 1) {
          ;
          flag = 1;
        } else {
          counter++;
        }
      }
      for (int i = 0; i < counter; i++) {
        argsources[*argsn][i] = row[i];
      }
      argsources[*argsn][counter] = '\0';
      *argsn = *argsn + 1;
    }

    fclose(pfile);
  } else {
    fprintf(stderr, "grep: %s: Нет такого файла или каталога\n", optarg);
    opt->err = 1;
  }

  return ex_code;
}

int printname(char *name, struct options *opt) {
  if (!opt->h || opt->l) {
    if (opt->l && opt->lprint == 0) {
      printf("%s", name);
      opt->lprint = 1;
    }
    if (!opt->l && opt->txtcount > 1) {
      printf("%s:", name);
    }
  }
  return 0;
}
int printnum(int strings_counter, struct options opt) {
  if (opt.n) {
    printf("%d:", strings_counter);
  }

  return 0;
}

int del_n_symbol(char *row) {
  int n = strlen(row);

  for (int i = 0; i < n; i++) {
    if (row[i] == '\n' || row[i] == '\0') {
      i = n;
    } else {
      printf("%c", row[i]);
    }
  }

  return 0;
}