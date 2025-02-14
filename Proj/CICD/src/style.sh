#/bin/bash
cp src/materials/linters/.clang-format -r cat grep
clang-format -n -Werror src/cat/s21_cat.c
clang-format -n -Werror src/grep/s21_grep.c
rm -rf src/cat/.clang-format grep/.clang-format