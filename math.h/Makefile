CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_math.h
SOURCES = $(wildcard functions/*.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: s21_math.a

s21_math.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_math.a $(OBJ_LIBRARY)
	ranlib s21_math.a
	rm -rf *.o

test: s21_math.a tests/s21_math_test.c
	gcc $(CFLAGS) tests/s21_math_test.c s21_math.a -o test.out -lm -lcheck
	./test.out

gcov_report: s21_math.a tests/s21_math_test.c
	gcc $(GCOVFLAGS) tests/s21_math_test.c $(SOURCES) -o report.out -lm -lcheck
	./report.out
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	xdg-open ./report/index-sort-f.html

style_check:
	clang-format -style=Google -n *.c *.h

rebuild: clean all

clean:
	rm -f functions/*.o 
	rm -f *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report

