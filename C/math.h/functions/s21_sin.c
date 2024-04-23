#include "../s21_math.h"

long double s21_sin(double x) {
  long double result;
  if (S21_IS_POS_INF(x) || S21_IS_NEG_INF(x) || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else {
    x = s21_fmod(x, 2 * S21_PI);
    while (x > S21_PI) {
      x -= 2 * S21_PI;
    }

    while (x < -S21_PI) {
      x += 2 * S21_PI;
    }
    result = x;
    int factorial = 1;
    long double temp = x;
    while (s21_fabs(temp) > S21_EPS) {
      temp = (-temp * x * x) / ((2 * factorial + 1) * (2 * factorial));
      result += temp;
      factorial++;
    }
  }

  return result;
}
