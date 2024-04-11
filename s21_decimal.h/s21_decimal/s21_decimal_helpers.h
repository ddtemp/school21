#ifndef S21_DECIMAL_HELPERS_H_
#define S21_DECIMAL_HELPERS_H_

#include "../s21_decimal.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum retutn_values { k_false = 0, k_true = 1, k_ok = 0, k_err = 1 };
enum comparison { k_equal, k_greater, k_less };

void s21_zero_decimal(s21_decimal *dst);
int s21_data_eq(const unsigned *data1, const unsigned *data2, int size);
int s21_data_gt(const unsigned *data1, const unsigned *data2, int size);
int s21_is_null(s21_decimal value);
int s21_get_scale(s21_decimal value);
void s21_to_scale(s21_decimal value, int scale, unsigned *result, int size);
void s21_negate_data(unsigned *value, int size);
void s21_div2mem(unsigned *value, int size);
void s21_div10mem(unsigned *value, unsigned *result, int size);
void s21_data_add(unsigned *buf_1, unsigned *buf_2, unsigned *buf_result,
                  int size);
void s21_set_scale(s21_decimal *dst, int scale);
int s21_mul10mem(unsigned *value, int size);
int s21_mod10mem(unsigned *value, int size);
int s21_get_sign(s21_decimal dst);
int s21_get_exponent(s21_decimal value);
int s21_divide_by_power_of_10(s21_decimal value, int power,
                              s21_decimal *result);
int s21_divide_by_integer(s21_decimal value, int integer, s21_decimal *result);
int s21_modulo_by_integer(s21_decimal value, int integer);
int s21_add_integer(s21_decimal value, int integer, s21_decimal *result);
int s21_multiply_by_integer_mem(unsigned *value, int size_v, int integer,
                                unsigned *result, int size_r);
void s21_data_sub(unsigned *buf_1, unsigned *buf_2, unsigned *buf_result,
                  int size);
void s21_mul_pow10mem(unsigned *value, int pow, int size);
int s21_get_bit(s21_decimal d, int i);



#endif  // S21_DECIMAL_HELPERS_H_
