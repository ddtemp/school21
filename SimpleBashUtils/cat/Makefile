CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

all: s21_cat

s21_cat: cat.c
	$(CC) $(FLAGS) cat.c -o s21_cat

test: s21_cat tests/test_func_cat.sh 
	cp s21_cat tests/
	cd tests/ && ./test_func_cat.sh

clean: 
	rm -rf s21_cat 
	rm -rf tests/s21_cat

