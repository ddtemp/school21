#ifndef S21_MATH
#define S21_MATH

#include <stdio.h>

#define S21_PI 3.14159265358979323846
#define S21_NAN 0.0 / 0.0
#define S21_POS_INF +1.0 / 0.0
#define S21_NEG_INF -1.0 / 0.0
#define S21_E 2.71828182845904523536028747

#define S21_IS_NAN(x) (x != x)
#define S21_IS_INF(x) (x == S21_NEG_INF || x == S21_POS_INF)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif // S21_MATH
