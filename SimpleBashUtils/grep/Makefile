FLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

all: s21_grep

s21_grep: grep.c
	gcc $(FLAGS) grep.c -o s21_grep

test: s21_grep grep_test.sh
	./grep_test.sh

clean:
	rm -f s21_grep
