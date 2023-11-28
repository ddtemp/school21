CC = gcc
CFLAGS = -Wall -Werror -Wextra
TARGET = s21_cat
TEST_SCRIPT = cat_test.sh

all: s21_cat

s21_cat: s21_cat.o
	gcc $(FLAGS) s21_cat.o -o s21_cat

s21_cat.o: cat.c
	gcc $(FLAGS) -c cat.c -o s21_cat.o

test: cat_test.sh
	./cat_test.sh

clean:
	rm -rf *.o
	rm -rf s21_cat
