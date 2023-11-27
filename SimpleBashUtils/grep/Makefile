FLAGS = -Wall -Werror -Wextra

all: s21_grep

s21_grep: grep.o
	gcc $(FLAGS) s21_grep.o -o s21_grep

grep.o: grep.c
	gcc $(FLAGS) -c grep.c -o s21_grep.o

rebuild:
	make clean
	make s21_grep

clean:
	rm -rf *.o
	rm -rf s21_grep
