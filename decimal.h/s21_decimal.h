#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int s21_less(s21_decimal value1, s21_decimal value2); 
int s21_lessOrEqual(s21_decimal value1, s21_decimal value2);
int s21_greater(s21_decimal value1, s21_decimal value2); 
int s21_greaterOrEqual(s21_decimal value1, s21_decimal value2);
int s21_equal(s21_decimal value1, s21_decimal value2); 
int s21_isNotEqual(s21_decimal value1, s21_decimal value2);

int s21_getSign(s21_decimal value);
int s21_setSign(s21_decimal *number, int sign);

int s21_getScale(s21_decimal value);
void s21_setScale(s21_decimal *value, int scale);
#endif // S21_DECIMAL_H
