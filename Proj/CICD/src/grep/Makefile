FLAGS =gcc -Wextra -Wall -Werror -std=c11

all : s21_grep

s21_grep: 
	$(FLAGS) ./s21_grep.c -o ./s21_grep

rebuild:
	make clean
	make all

clean:
	rm -rf ./s21_grep

s21_grep_test: 
	sh grep_test.sh

test : rebuild s21_grep s21_grep_test