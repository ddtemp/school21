#include "../s21_math.h"

long double doubleFactorial(long x) {
  long double factorial = 1;
  if (x % 2 == 0) {
    for (int i = 2; i <= x; i += 2) {
      factorial *= i;
    }
  } else {
    for (int i = 1; i <= x; i += 2) {
      factorial *= i;
    }
  }

  return factorial;
}

long double s21_asin(double x) {
  long double result = x;
  if (x > 1.0 || x < -1.0 || S21_IS_NAN(x)) {
    result = S21_NAN;
  } else if (x == 1) {
    result = S21_PI / 2;
  } else if (x == -1) {
    result = -S21_PI / 2;
  } else {
    int i = 1;
    while (i < 100000) {
      long double factorial =
          (doubleFactorial(2 * i - 1) * s21_pow(x, 2 * i + 1)) /
          (doubleFactorial(2 * i) * (2 * i + 1));
      if (factorial < 0.0000000000001L && factorial > -0.0000000000001L) {
        break;
      }
      result += factorial;
      i++;
    }
  }
  return result;
}
