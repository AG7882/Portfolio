FLAGS =gcc -Wextra -Wall -Werror -std=c11

all : s21_cat 

s21_cat: 
	$(FLAGS) ./s21_cat.c -o ./s21_cat

s21_cat_test: 
	sh cat_test.sh


rebuild:
	make clean
	make all

clean:
	rm -rf ./s21_cat

test : rebuild s21_cat s21_cat_test
