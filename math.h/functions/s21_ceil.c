#include "../s21_math.h"

long double s21_ceil(double x) {
  long double ceil_x = (long long int)x;
  if (S21_IS_NAN(x)) {
    ceil_x = S21_NAN;
  } else if (S21_IS_POS_INF(x)) {
    ceil_x = S21_POS_INF;
  } else if (S21_IS_NEG_INF(x)) {
    ceil_x = S21_NEG_INF;
  } else if (x > 0 && x != ceil_x) {
    ceil_x += 1;
  }

  return ceil_x;
}
// если x равен нулю, он не изменится при округлении в большую сторону
