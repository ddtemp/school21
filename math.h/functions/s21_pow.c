#include "../s21_math.h"

long double exceptionsCheck(double base, double exp) {
  double result = -2.0;

  if (base == 0.0) {
    if (S21_IS_NAN(exp)) {
      result = S21_NAN;
    } else if (S21_IS_NEG_INF(exp)) {
      result = S21_POS_INF;
    } else if (exp == 0.0) {
      result = 1.0;
    } else if (exp < 0) {
      result = S21_POS_INF;
    }
  } else if (base == 1.0) {
    result = 1.0;
  } else if (base == -1.0) {
    if (S21_IS_POS_INF(exp) || S21_IS_NEG_INF(exp)) {
      result = 1.0;
    }
  } else if (base == (__builtin_nanf(""))) {
    result = S21_NAN;
  } else if (S21_IS_INT(base)) {
    if (S21_IS_POS_INF(exp)) {
      result = S21_POS_INF;
    } else if (S21_IS_NEG_INF(exp)) {
      result = 0.0;
    }
  } else if (S21_IS_POS_INF(base)) {
    if (exp == 0.0) {
      result = 1.0;
    } else if (exp > 0 && S21_IS_INT(exp)) {
      result = S21_POS_INF;
    } else if (S21_IS_POS_INF(exp)) {
      result = S21_POS_INF;
    } else if (S21_IS_NAN(exp)) {
      result = S21_NAN;
    }
  } else if (S21_IS_NEG_INF(base)) {
    if (exp == 0.0) {
      result = 1.0;
    } else if (exp > 0 && S21_IS_INT(exp)) {
      result = S21_NEG_INF;
    } else if (S21_IS_POS_INF(exp)) {
      result = S21_POS_INF;
    } else if (S21_IS_NAN(exp)) {
      result = S21_NAN;
    } else if (S21_IS_NEG_INF(exp)) {
      result = 0;
    }
  }

  return result;
}

long double fastVersionOfPow(double base, long long int exp) {
  long double result = 1.0;
  long long absExp = s21_abs(exp);

  while (absExp) {
    result *= base;
    absExp--;
  }
  return (exp < 0) ? 1.0 / result : result;
}

long double s21_pow(double base, double exp) {
  long double result = exceptionsCheck(base, exp);
  if (result == -2.0) {
    if (S21_IS_INT(exp)) {
      result = fastVersionOfPow(base, exp);
    } else {
      result = s21_exp(exp * s21_log(base));
    }
  }
  return result;
}
