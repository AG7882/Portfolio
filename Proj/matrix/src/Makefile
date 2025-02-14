CC = gcc
CFLAGS = -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov  
CHECK_FLAGS = -lcheck -lm -lpthread -lsubunit
LDFLAGS = -L. -ls21_matrix --coverage
TFLAGS = -std=c11 -g

SRCS =  functions/*.c

TEST_SRCS = tests.c

all: rebuild s21_matrix.a test gcov_report

rebuild: clean s21_matrix.a



test: rebuild
	$(CC)  $(TFLAGS) tests.c libs21_matrix.a $(CHECK_FLAGS) -L.   -ls21_matrix 
	./a.out

test_valgrind: test
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes ./a.out

gcov_report: s21_matrix.a 
	rm -f *.g*
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCS) tests.c libs21_matrix.a $(CHECK_FLAGS) $(GCOV_FLAGS) -lm -lsubunit
	./a.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open ./gcov_report/index.html
	

clean:
	rm -rf *.o *.a *.info *.out gcov_report  *.gcda *.gcno


style:
	cp ../materials/linters/.clang-format .
	find .. -name "*.c" -exec clang-format -i {} \;
	find .. -name "*.h" -exec clang-format -i {} \;
	rm -rf .clang-format

style_test:
	cp ../materials/linters/.clang-format .
	find .. -name "*.c" -exec clang-format -n {} \;
	find .. -name "*.h" -exec clang-format -n {} \;
	rm -rf .clang-format

s21_matrix.o:
	$(CC) $(CFLAGS)  -c  $(SRCS) -lm

s21_matrix.a: s21_matrix.o
	ar rcs libs21_matrix.a *.o
	rm -rf *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a
	cp libs21_matrix.a ls21_matrix.a



