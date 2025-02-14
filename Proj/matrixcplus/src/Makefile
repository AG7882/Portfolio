CC = g++
CFLAGS = -std=c++17 -g -Wall -Werror -Wextra
GTEST_FLAGS = -fprofile-arcs -ftest-coverage -lgcov -lgtest -lgtest_main -lrt -lstdc++ -pthread


SRCS =  functions/*.cpp


all: rebuild s21_matrix_oop.a test gcov_report

rebuild: clean s21_matrix_oop.a



test: clean
	$(CC)  $(CFLAGS) tests.cc $(SRCS) $(GTEST_FLAGS) --coverage -fno-elide-constructors
	./a.out

test_valgrind: test
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes ./a.out

gcov_report: test
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

s21_matrix_oop.a: s21_matrix.o
	ar rcs libs21_matrix.a *.o
	rm -rf *.o



