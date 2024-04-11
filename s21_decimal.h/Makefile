PROJECT = s21_decimal

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
CHECKFLAGS = -lcheck
else
CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

SOURCES = $(wildcard $(PROJECT)/s21_decimal_*.c)
TESTS = $(wildcard tests/*.c)
STYLEFILES = $(wildcard *.c $(PROJECT)/*.c tests/*.c)
SOURSEOBJ := $(patsubst $(PROJECT)/%.c, build/%.o, $(SOURCES))

all: $(PROJECT).a

build/%.o: $(PROJECT)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT).a: $(SOURSEOBJ)
	ar rcs $@ $^
	ranlib $@

test: $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $^ -o test.out
	./test.out

gcov_report: $(PROJECT).a $(SOURCES) $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $(GCOVFLAGS) $^ -o test_gcov.out
	./test_gcov.out
	lcov -t "gcov_report" -o coverage.info --no-external -c -d .
	@genhtml -q coverage.info -o ./tests/report
	@mv *.gcda *.gcno *.info ./build
	open ./tests/report/index.html

style:
	@clang-format -style=Google -n $(STYLEFILES)

clean:
	@rm -rf $(PROJECT).a ./tests/report ./build/* *.out *.gcda *.gcno *.info

rebuild: clean all

.PHONY: all $(PROJECT).a test gcov_report style clean rebuild
