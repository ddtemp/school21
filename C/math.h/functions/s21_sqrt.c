#include "../s21_math.h"

long double s21_sqrt(double x) {
  if (S21_IS_NAN(x) || x == S21_NEG_INF || x < 0) return S21_NAN;
  if (x == S21_POS_INF || x == 0) return (long double)x;

  return s21_pow(x, 0.5);
}
