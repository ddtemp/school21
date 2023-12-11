#include "../s21_math.h"

long double s21_tan(double x) {
  long double result;

  if (S21_IS_NAN(s21_cos(x))) {
    result = S21_NAN;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}
