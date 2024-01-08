#include "../s21_math.h"

long double s21_acos(double x) {
  long double result;
  if (x > 1.0 || x < -1.0 || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else if (x == 1) {
    result = 0;
  } else if (x == -1) {
    result = S21_PI;
  } else {
    result = (S21_PI / 2) - s21_asin(x);
  }

  return result;
}
