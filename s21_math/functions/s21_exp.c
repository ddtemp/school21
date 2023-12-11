#include "../s21_math.h"

long double s21_exp(double x) {
  long double result = 1.0;

  if (S21_IS_POS_INF(x)) {
    result = S21_POS_INF;
  } else if (S21_IS_NAN(x)) {
    result = S21_NAN;
  } else if (S21_IS_NEG_INF(x)) {
    result = 0;
  } else {
    int termCounter = 1;
    long double term = 1.0, helper = x;
    if (x < 0.0) helper = -x;
    for (int i = 0; i < 1600; i++) {
      term *= helper / termCounter++;
      result += term;
    }
    if (x < 0.0) result = 1 / result;
  }
  return result;
}
