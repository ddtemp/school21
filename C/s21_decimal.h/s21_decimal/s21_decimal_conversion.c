#include "../s21_decimal.h"
#include "s21_decimal_helpers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  dst->bits[3] = src & 0x80000000;

  dst->bits[0] = (abs(src));
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 0;
  *dst = 0;

  s21_truncate(src, &src);
  if (src.bits[2] || src.bits[1] || src.bits[0] > 0x7fffffff) {
    status = 1;
  }
  *dst = (src.bits[3] & 0x80000000) ? -(src.bits[0] & 0x7fffffff)
                                    : src.bits[0] & 0x7fffffff;

  return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double tmp = 0;
  int scale = s21_get_scale(src);

  for (int i = 0; i < 96; i++) {
    tmp *= 2;
    if (s21_get_bit(src, 95 - i)) tmp += 1;
  }
  while (scale > 0) {
    tmp /= 10;
    scale--;
  }
  if (s21_get_sign(src)) tmp *= -1;
  *dst = (float)tmp;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_zero_decimal(dst);
  int return_value = 0;
  if (isinf(src) || isnan(src)) {
    return_value = 1;
  } else {
    if (src != 0) {
      int sign = *(int *)&src >> 31;
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
      }
      temp = round(temp);
      if (off <= 28 && (exp > -94 && exp < 96)) {
        floatbits mant = {0};
        temp = (float)temp;
        for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
        }
        mant.fl = temp;
        exp = ((*(int *)&mant.fl & ~0x80000000) >> 23) - 127;
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
        dst->bits[3] = (sign << 31) | (off << 16);
      }
    }
  }
  return return_value;
}
