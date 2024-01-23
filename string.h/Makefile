.PHONY: all clean test s21_string.a gcov_report
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
CHECKFLAGS = -lcheck
else
CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

SOURCES = $(wildcard functions/*.c)
TESTS = $(wildcard tests/*.c) 
SOURSEOBJ := $(patsubst %.c, %.o, $(SOURCES))
TESTOBJ := $(patsubst %.c, %.o, $(TESTS))
STYLE = $(wildcard *.c *.h functions/*.c tests/*.c)

all: s21_string.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

s21_string.a: $(SOURSEOBJ)
	@ar rcs $@ $^
	@ranlib $@
	@rm $^

test: s21_string.a $(TESTS) runtests.c
	@$(CC) $(CFLAGS) $(CHECKFLAGS) $^ -o test.out
	./test.out

gcov_report: s21_string.a $(SOURCES) $(TESTS) runtests.c
	@$(CC) $(CFLAGS) $(CHECKFLAGS) $(GCOVFLAGS) $^ -o test_gcov.out
	./test_gcov.out 
	@lcov -t "gcov_report" -o coverage.info --no-external -c -d .
	@genhtml -q coverage.info -o ./report 
	@mv *.gcda *.gcno *.info ./report
	open ./report/index.html

style:
	@clang-format -style=Google -n $(STYLE)

rebuild: clean all

clean:
	rm -rf ./report *.out s21_string.a *.gcda *.gcno *.info functions/*.o
