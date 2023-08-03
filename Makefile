CC=gcc
FLAGS=-Wall -Werror -Wextra
GCOVFLAGS=
DEBUGFLAGS=

SRC=$(wildcard ./function_files/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

all: s21_decimal.a

debug: CC=g++
debug: DEBUGFLAGS=-g2
debug: main

s21_decimal.a: ${OBJ}
	ar rcs s21_decimal.a $^

%.o: %.c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(GCOVFLAGS) -c $^ -o $@

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf function_files/*.o
	rm -rf main
	rm -rf *.dSYM
	rm -rf *.out
	rm -rf test
	rm -rf gcov_report
	rm -rf *.info
	rm -rf *.gcda
	rm -rf *.gcno

build_test: FLAGS=
build_test: s21_decimal.a
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(GCOVFLAGS) test.c -L. s21_decimal.a -lcheck -o test

test: build_test
	./test

gcov_report: GCOVFLAGS += --coverage -fprofile-arcs -ftest-coverage
gcov_report: DEBUGFLAGS += -g2
gcov_report: clean test
gcov_report:
	geninfo ./ -b ./ -o ./coverage.info
	genhtml coverage.info -o gcov_report
