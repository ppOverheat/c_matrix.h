UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	COMMANDS=dos2unix info.sh leak_info.sh
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=leaks -quiet -atExit --
	COMMANDS=
endif
CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage

all: s21_matrix.a

style:
	clang-format -n -style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

s21_matrix.a: clean
	gcc $(CFLAGS) -c s21_matrix.c
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -f *.o

test: s21_matrix.a
	gcc $(CFLAGS) test.c s21_matrix.a -L. $(LFLAGS) -o test
	-./test > test.log
	bash info.sh

leaks: s21_matrix.a
	gcc $(CFLAGS) test.c s21_matrix.a -L. $(LFLAGS) -o test
	$(LEAK) ./test > test.log
	$(COMMANDS)
	bash info.sh
	bash leak_info.sh

gcov_report: clean
	gcc $(GFLAGS) $(CFLAGS) s21_matrix.c test.c $(LFLAGS) -o test
	-./test > test.log
	bash info.sh
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -f test test1 *.a *.log *.xml *.gcda *.gcno *.info
	rm -rf report
