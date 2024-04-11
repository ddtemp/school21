PROJECT_NAME = s21_matrix
CC = gcc
FLAGS = -Werror -Wall -Wextra -std=c11
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
  CC2 += -D OS_MAC
else
  CC2 += -D OS_LINUX
endif


all: $(PROJECT_NAME).a

$(PROJECT_NAME).a: clean
	$(CC) $(FLAGS) -c s21_*.c
	ar rcs $(PROJECT_NAME).a *.o

clean:
	rm -rf *.g* *.info report *.a *.out *.o s21_test s21_matrix_test.c

test: clean $(PROJECT_NAME).a
	echo "#include \"s21_matrix.h\"" > $(PROJECT_NAME)_test.c
	checkmk clean_mode=1 test/s21_*.check >> $(PROJECT_NAME)_test.c
ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) $(PROJECT_NAME)_test.c $(PROJECT_NAME).a -o s21_test -lcheck
	./s21_test
else	
	$(CC) $(FLAGS) $(PROJECT_NAME)_test.c $(PROJECT_NAME).a -o s21_test -lcheck -lsubunit -lrt -lpthread -lm
	./s21_test
endif

gcov_report: clean
	echo "#include \"s21_matrix.h\"" > $(PROJECT_NAME)_test.c
	checkmk clean_mode=1 test/*.check >> $(PROJECT_NAME)_test.c
ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) --coverage s21_*.c -o s21_test -lcheck
	./s21_test
	lcov -t "s21_test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
else	
	$(CC) $(FLAGS) --coverage s21_*.c -o s21_test -lcheck -lsubunit -lrt -lpthread -lm
	./s21_test 
	lcov -t "s21_test" -o test.info -c -d .
	genhtml -o report test.info
	xdg-open ./report/index.html
endif

style:
	clang-format -style=google -n *.c

format:
	clang-format -style=google -i *.c

ending:
	cppcheck *.h *.c
	clang-format -style=Google -i *.h *.c
	valgrind --leak-check=full --show-leak-kinds=all ./s21_test