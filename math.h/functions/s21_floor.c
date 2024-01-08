#include "../s21_math.h"

long double s21_floor(double x) {
  long double floor_x = (long long int)x;
  if (S21_IS_NAN(x)) {
    floor_x = S21_NAN;
  } else if (S21_IS_POS_INF(x)) {
    floor_x = S21_POS_INF;
  } else if (S21_IS_NEG_INF(x)) {
    floor_x = S21_NEG_INF;
  } else if (x < 0 && x != floor_x) {
    floor_x -= 1;
  }

  return floor_x;
}
