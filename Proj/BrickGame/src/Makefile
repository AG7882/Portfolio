CC = gcc -std=c11 -D_POSIX_C_SOURCE=199309L
CFLAGS = -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov  
CHECK_FLAGS = -lcheck -lm -lpthread -lsubunit
LDFLAGS = -L. -ls21_matrix --coverage
TARGET = tetris.out


TEST_SRCS = tests.c

all: install

rebuild: clean install



test: 
	$(CC) -DTEST_MODE tests.c brick_game/tetris/tetris.c gui/cli/gui.c $(CHECK_FLAGS) -L. -lncurses -o t.out
	./t.out

valgrind: install
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes ./tetris.out

gcov_report: rebuild
	rm -f *.g*
	$(CC) $(CFLAGS) -DTEST_MODE tests.c brick_game/tetris/tetris.c gui/cli/gui.c -lncurses $(CHECK_FLAGS) $(GCOV_FLAGS) -lm -lsubunit
	./a.out
	lcov --capture --directory . --output-file coverage.info --include 'brick_game/tetris/tetris.c'
	genhtml coverage.info --output-directory gcov_report
	open ./gcov_report/index.html
	

clean:
	rm -rf *.o *.a *.info *.out gcov_report  *.gcda *.gcno game


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

install:
	 $(CC) $(CFLAGS) brick_game/tetris/tetris.c gui/cli/gui.c -lpthread -lncurses -o $(TARGET) 

uninstall: clean
	rm -rf $(TARGET)  highscore.txt

launch: 
	./$(TARGET) 

dist: clean install
	mkdir -p game
	#cp -r tetris.out game
	tar -czf game.tar tetris.out


	
