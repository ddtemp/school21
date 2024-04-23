#include "../s21_math.h"
int isNegative(long double x) { return x > 0 ? 1 : 0; }
long double s21_atan(double x) {
  long double result = 0;

  if (x < 1.0 && x > -1.0) {
    for (int i = 0; i < 400; i++) {
      result +=
          s21_pow(-1.0, i) * s21_pow(x, 1.0 + (2.0 * i)) / (1.0 + (2.0 * i));
    }
  } else {
    for (int i = 0; i < 400; i++) {
      result +=
          s21_pow(-1.0, i) * s21_pow(x, -1.0 - 2.0 * i) / (1.0 + (2.0 * i));
    }
    result = ((S21_PI * s21_sqrt(x * x)) / (2.0 * x)) - result;
  }

  if (s21_fabs((float)x) == 1.0) {
    result = isNegative(result) ? (S21_PI / 4) : -(S21_PI / 4);
  } else if (s21_fabs(x) == S21_POS_INF) {
    result = isNegative(x) ? -(S21_PI / 2) : (S21_PI / 2);
  }

  if (x == S21_NAN || x == S21_POS_INF || S21_IS_NAN(x)) result = S21_NAN;

  return result;
}
