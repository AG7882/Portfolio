#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>
#include <string.h>

struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int txtcount;
  int strcount;
  int lprint;
  int err;
};

int search(char **argv, int argn);
int open_file(char *pos, int *args_count, char args_e[256][256],
              struct options *opt);
int options_filler(int argn, int *args_count, char args_e[256][256],
                   int *file_count, char file_e[256][256], char **argv,
                   struct options *opt);
int options_filler2nd(char chr, int index, int *file_count,
                      char file_e[256][256], char **argv, struct options *opt);
int options_add(int number, int *args_count, char args_e[256][256], char **argv,
                struct options *opt);
int options_add_sec(int i, int j, int *args_count, char args_e[256][256],
                    char **argv, struct options *opt);
int search_file(int *args_count, char *name, char args_e[256][256], FILE *pfile,
                struct options *opt);
int parse(int args_count, int snumber, int regexcount, int *results,
          int *compresult, char *row, char *name, char args_e[256][256],
          regex_t *regex, struct options *opt);
int parse2nd(int *is_found, int length, int pos, int *is_in_row, int *forv,
             regmatch_t *mass, int snumber, int regexcount, int *compresult,
             char *row, char *name, char args_e[256][256], regex_t *regex,
             struct options *opt);
int forparse(int is_found, int snumber, int length, unsigned int *i, char *name,
             char *row, struct options *opt);
int check(char *line, char chr);
int checklast(char *line, char chr, char chr2);
int addarg(int i, unsigned int j, char **argv, char eorf, char args_e[256][256],
           int *args_count);
int print_all(int snumber, char *line, char *name, struct options *opt);
int f_counter(char *optarg, int *argsn, char argsources[256][256],
              struct options *opt);
int printname(char *name, struct options *opt);
int printnum(int strings_counter, struct options opt);

int del_n_symbol(char *row);

#endif
