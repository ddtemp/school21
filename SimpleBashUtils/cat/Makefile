FLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o
	gcc $(FLAGS) s21_cat.o -o s21_cat
	rm -rf s21_cat.o
s21_cat.o: cat.c
	gcc $(FLAGS) -c cat.c -o s21_cat.o

clean:
	rm -rf *.o
	rm -rf s21_cat
