#include "../s21_math.h"

long double s21_log(double x) {
  int exponent = 0;
  long double result = 0;
  long double exPow = 0;

  if (S21_IS_NAN(x) || S21_IS_NEG_INF(x)) {
    result = S21_NAN;
  } else if (S21_IS_POS_INF(x)) {
    result = S21_POS_INF;
  } else {
    if (x < 0) {
      result = S21_NAN;
    } else if (x != 0) {
      for (; x >= S21_E; x /= S21_E, exponent++) continue;

      for (int i = 0; i < 100; i++) {
        exPow = result;
        result = exPow + 2 * (x - s21_exp(exPow)) / (x + s21_exp(exPow));
      }
    } else {
      result = S21_NEG_INF;
    }
  }
  return (result + exponent);
}
