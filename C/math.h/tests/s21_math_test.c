#include "../s21_math.h"
#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(abs_test_1) {
  ck_assert_double_eq(abs(-2), s21_abs(-2));
  ck_assert_double_eq(abs(-94), s21_abs(-94));
  ck_assert_double_eq(abs(153), s21_abs(153));
  ck_assert_double_eq(abs(10099), s21_abs(10099));
  ck_assert_double_eq(abs(-10099), s21_abs(-10099));
}
END_TEST

START_TEST(abs_test_2) {
  ck_assert_int_eq(s21_abs(-10), abs(-10));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(-229), abs(-229));
  ck_assert_int_eq(s21_abs(14), abs(14));
}
END_TEST

START_TEST(acos_test_1) {
  for (float k = -1; k <= 1; k += 0.1) {
    double a = s21_acos(k);
    double b = acos(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(acos_test_2) {
  for (float k = -1; k <= 1; k += 0.425) {
    double a = s21_acos(k);
    double b = acos(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(acos_test_3) {
  double a = s21_acos(1);
  double b = acos(1);
  ck_assert_double_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(acos_test_4) {
  double a = s21_acos(0);
  double b = acos(0);
  ck_assert_double_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(asin_test_1) {
  for (float k = -1; k <= 1; k += 0.1) {
    double a = s21_asin(k);
    double b = asin(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
  ck_assert_double_eq_tol(asin(1), s21_asin(1), 1e-6);
}
END_TEST

START_TEST(asin_test_2) {
  for (float k = -1; k <= 1; k += 0.0882) {
    double a = s21_asin(k);
    double b = asin(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(atan_test_1) {
  double a = 11;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = 0.3;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = -0.7;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = -0.333;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = 18.23;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = S21_E;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
  a = 1.0;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-6);
}
END_TEST

START_TEST(atan_test_2) {
  for (float k = -20; k <= 20; k += 6) {
    double a = s21_atan(k);
    double b = atan(k);
    printf("\n%lf\n", k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(ceil_test) {
  ck_assert_double_eq(ceil(INFINITY), s21_ceil(S21_POS_INF));
  ck_assert_double_eq(ceil(-INFINITY), s21_ceil(S21_NEG_INF));
  ck_assert_double_nan(ceil(NAN));
  ck_assert_double_nan(s21_ceil(S21_NAN));
  ck_assert_double_eq(ceil(-7.0), s21_ceil(-7.0));
  ck_assert_double_eq(ceil(-98.1), s21_ceil(-98.1));
  ck_assert_double_eq(ceil(123.02), s21_ceil(123.02));
  ck_assert_double_eq(ceil(10009.00123), s21_ceil(10009.00123));
  ck_assert_double_eq(ceil(-10009.555), s21_ceil(-10009.555));
  ck_assert_double_eq(ceil(-0.10009), s21_ceil(-0.10009));
  ck_assert_double_eq(ceil(-1e-23), s21_ceil(-1e-23));
}
END_TEST

START_TEST(cos_test_1) {
  for (double r = 0.0; r <= 2 * M_PI; r += 0.01) {
    ck_assert_double_eq_tol(cos(r), s21_cos(r), 1e-6);
  }
}
END_TEST

START_TEST(cos_test_2) {
  ck_assert_ldouble_nan(s21_cos(S21_POS_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NEG_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  ck_assert_ldouble_nan(s21_cos(-S21_NAN));
  ck_assert_ldouble_eq_tol(s21_cos(0.5), cos(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-0.5), cos(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-1), cos(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(1), cos(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(5.7), cos(5.7), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-3.1), cos(-3.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0), cos(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-0), cos(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(5.123456789123), cos(5.123456789123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0.00000004562177), cos(0.00000004562177),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(14672.123), cos(14672.123), 1e-6);
}
END_TEST

START_TEST(exp_test_1) {
  for (double k = -6; k < 6; k += 0.00573) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_2) {
  ck_assert_double_nan(s21_exp(S21_NAN));
  ck_assert_double_eq(exp(INFINITY), s21_exp(S21_POS_INF));
  ck_assert_double_eq(exp(-INFINITY), s21_exp(S21_NEG_INF));
  ck_assert_double_eq(exp(-5.123), s21_exp(-5.123));
  ck_assert_double_eq(exp(0), s21_exp(0));
  ck_assert_double_eq(exp(1), s21_exp(1));
  ck_assert_double_eq(exp(510), s21_exp(510));
}
END_TEST

START_TEST(exp_test_3) {
  for (double k = -25; k < 25; k += 1) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_4) {
  for (double k = -11; k < 11; k += 0.123) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(fabs_test) {
  ck_assert_double_eq(fabs(INFINITY), s21_fabs(S21_POS_INF));
  ck_assert_double_eq(fabs(-INFINITY), s21_fabs(S21_NEG_INF));
  ck_assert_double_nan(fabs(NAN));
  ck_assert_double_nan(s21_fabs(S21_NAN));
  ck_assert_double_eq(fabs(-6.0), s21_fabs(-6.0));
  ck_assert_double_eq(fabs(-10009.666), s21_fabs(-10009.666));
  ck_assert_double_eq(fabs(-0.10009), s21_fabs(-0.10009));
  ck_assert_double_eq(fabs(-1e23), s21_fabs(-1e23));
  ck_assert_double_eq(fabs(-98.1), s21_fabs(-98.1));
  ck_assert_double_eq(fabs(123.12), s21_fabs(123.12));
  ck_assert_double_eq(fabs(10009.0), s21_fabs(10009.0));
}
END_TEST

START_TEST(floor_test) {
  ck_assert_double_eq(floor(INFINITY), s21_floor(S21_POS_INF));
  ck_assert_double_eq(floor(-INFINITY), s21_floor(S21_NEG_INF));
  ck_assert_double_nan(s21_floor(S21_NAN));
  ck_assert_double_nan(floor(NAN));
  ck_assert_double_eq(floor(-7.0), s21_floor(-7.0));
  ck_assert_double_eq(floor(-98.1), s21_floor(-98.1));
  ck_assert_double_eq(floor(123.02), s21_floor(123.02));
  ck_assert_double_eq(floor(10009.00123), s21_floor(10009.00123));
  ck_assert_double_eq(floor(-10009.555), s21_floor(-10009.555));
  ck_assert_double_eq(floor(-0.10009), s21_floor(-0.10009));
  ck_assert_double_eq(floor(-1e-23), s21_floor(-1e-23));
  ck_assert_double_eq(floor(210004674.5), s21_floor(210004674.5));
}
END_TEST

START_TEST(fmod_test_1) {
  for (double a = -2500; a < 2500; a += 234) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
}
END_TEST

START_TEST(fmod_test_2) {
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_POS_INF));
  ck_assert_double_nan(s21_fmod(S21_POS_INF, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NEG_INF));
  ck_assert_double_nan(s21_fmod(S21_NEG_INF, S21_NAN));
  ck_assert_double_nan(fmod(NAN, INFINITY));
  ck_assert_double_nan(fmod(INFINITY, NAN));
  ck_assert_double_nan(fmod(NAN, -INFINITY));
  ck_assert_double_nan(fmod(-INFINITY, NAN));
  ck_assert_double_nan(fmod(1, 0));
  ck_assert_double_nan(s21_fmod(1, 0));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_nan(fmod(INFINITY, -1));
  ck_assert_double_nan(s21_fmod(INFINITY, -1));
  ck_assert_double_eq(fmod(-1, -INFINITY), s21_fmod(-1, S21_NEG_INF));
  ck_assert_double_eq(fmod(0, INFINITY), s21_fmod(0, S21_POS_INF));
  ck_assert_double_nan(s21_fmod(0, S21_NAN));
  ck_assert_double_nan(fmod(0, NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_double_nan(fmod(NAN, NAN));
}
END_TEST

START_TEST(log_test_1) {
  for (double k = 0.1; k < 4; k += 0.34) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_2) {
  ck_assert_double_nan(s21_log(S21_NAN));
  ck_assert_double_nan(log(NAN));
  ck_assert_double_eq(log(0), s21_log(0));
  ck_assert_double_nan(log(-3));
  ck_assert_double_nan(s21_log(S21_NEG_INF));
  ck_assert_double_nan(log(-INFINITY));
  ck_assert_double_eq(log(M_E), s21_log(S21_E));
  ck_assert_double_eq_tol(log(2), s21_log(2), 1e-6);
}
END_TEST

START_TEST(log_test_3) {
  for (double k = 0.1; k < 10000; k += 123) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_4) {
  for (double k = 1; k < 100; k += 14.2) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_5) {
  for (double k = 0.05; k < 10; k *= 5) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(pow_test_1) {
  ck_assert_double_eq(pow(1, 0), s21_pow(1, 0));
  ck_assert_double_eq(pow(0, 0), s21_pow(0, 0));
  ck_assert_double_eq(pow(0, -1), s21_pow(0, -1));
  ck_assert_double_eq(pow(0, 1), s21_pow(0, 1));
  ck_assert_double_eq(pow(INFINITY, 0), s21_pow(S21_POS_INF, 0));
  ck_assert_double_eq(pow(INFINITY, -1), s21_pow(S21_POS_INF, -1));
  ck_assert_double_eq(pow(0, INFINITY), s21_pow(0, S21_POS_INF));
  ck_assert_double_nan(s21_pow(0, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_eq(pow(INFINITY, INFINITY),
                      s21_pow(S21_POS_INF, S21_POS_INF));
  ck_assert_double_eq(pow(INFINITY, -INFINITY),
                      s21_pow(S21_POS_INF, S21_NEG_INF));
  ck_assert_double_eq(pow(-INFINITY, -INFINITY),
                      s21_pow(S21_NEG_INF, S21_NEG_INF));
  ck_assert_double_nan(s21_pow(INFINITY, S21_NAN));
  ck_assert_double_nan(s21_pow(-INFINITY, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_POS_INF));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NEG_INF));
  ck_assert_double_eq(pow(2, INFINITY), s21_pow(2, S21_POS_INF));
  ck_assert_double_eq(pow(0.5, INFINITY), s21_pow(0.5, S21_POS_INF));
  ck_assert_double_eq(pow(2, -INFINITY), s21_pow(2, S21_NEG_INF));
  ck_assert_double_eq(pow(0.5, -INFINITY), s21_pow(0.5, S21_NEG_INF));
  ck_assert_double_eq(pow(-2, -INFINITY), s21_pow(-2, S21_NEG_INF));
  ck_assert_double_eq(pow(0.0, INFINITY), s21_pow(0.0, S21_POS_INF));
  ck_assert_double_eq(pow(0.0, -INFINITY), s21_pow(0.0, S21_NEG_INF));
  ck_assert_double_eq(pow(INFINITY, 5), s21_pow(S21_POS_INF, 5));
  ck_assert_double_eq(pow(-1.0, -INFINITY), s21_pow(-1.0, S21_NEG_INF));
  ck_assert_double_eq(pow(-INFINITY, 0), s21_pow(S21_NEG_INF, 0));
  ck_assert_double_eq(pow(-INFINITY, 7), s21_pow(S21_NEG_INF, 7));
  ck_assert_double_eq(pow(-INFINITY, INFINITY),
                      s21_pow(S21_NEG_INF, S21_POS_INF));
}
END_TEST

START_TEST(pow_test_2) {
  for (double k = -9; k <= 9; k += 1.7) {
    for (double g = -5; g < 5; g += 1) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-6);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_3) {
  for (double k = -1e-1; k <= 1; k += 1.1e-1) {
    for (double g = -2.55; g < 2; g += 1.1) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-6);
      }
    }
  }
}
END_TEST

START_TEST(sin_test_1) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * S21_PI; k > -2 * S21_PI; k -= S21_PI / 17) {
      ck_assert_double_eq_tol(sin(k + R * S21_PI), s21_sin(k + R * S21_PI),
                              1e-6);
    }
  }
}
END_TEST

START_TEST(sin_test_2) {
  ck_assert_ldouble_nan(s21_sin(S21_POS_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NEG_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
  ck_assert_ldouble_nan(s21_sin(-S21_NAN));
  ck_assert_ldouble_eq_tol(s21_sin(0.5), sin(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-0.5), sin(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-1), sin(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1), sin(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1.1), sin(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-2.1), sin(-2.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-0), sin(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(5.123456789123), sin(5.123456789123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0.00000004564897), sin(0.00000004564897),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1234.188), sin(1234.188), 1e-6);
}
END_TEST

START_TEST(sqrt_test_1) {
  for (double k = 0; k < 24; k += 3) {
    double a = s21_sqrt(k);
    double b = sqrt(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(sqrt_test_2) {
  ck_assert_double_nan(s21_sqrt(S21_NAN));
  ck_assert_double_nan(sqrt(NAN));
  ck_assert_double_eq(s21_sqrt(S21_POS_INF), sqrt(INFINITY));
  ck_assert_double_nan(s21_sqrt(S21_NEG_INF));
  ck_assert_double_nan(sqrt(-INFINITY));
  ck_assert_double_nan(s21_sqrt(-5));
  ck_assert_double_nan(sqrt(-5));
  ck_assert_double_eq_tol(s21_sqrt(1000), sqrt(1000), 1e-6);
}
END_TEST

START_TEST(tan_test_1) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * S21_PI; k > -2 * S21_PI; k -= S21_PI / 9) {
      ck_assert_double_eq_tol(tan(k + R * S21_PI), s21_tan(k + R * S21_PI),
                              1e-6);
    }
  }
}
END_TEST

START_TEST(tan_test_2) {
  ck_assert_ldouble_nan(s21_cos(S21_POS_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NEG_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  ck_assert_ldouble_nan(s21_cos(-S21_NAN));
  ck_assert_ldouble_eq_tol(s21_tan(0.5), tan(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-0.5), tan(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-1), tan(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1.1), tan(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-2.1), tan(-2.1), 1e-8);
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-0), tan(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(0.00000004564897), tan(0.00000004564897),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1234.188), tan(1234.188), 1e-6);
}
END_TEST

START_TEST(sin_cos_tan_test) {
  ck_assert_double_nan(s21_sin(S21_NAN));
  ck_assert_double_nan(s21_cos(S21_NAN));
  ck_assert_double_nan(s21_tan(S21_NAN));
  ck_assert_double_nan(s21_sin(S21_POS_INF));
  ck_assert_double_nan(s21_cos(S21_POS_INF));
  ck_assert_double_nan(s21_tan(S21_POS_INF));
  ck_assert_double_nan(s21_sin(S21_NEG_INF));
  ck_assert_double_nan(s21_cos(S21_NEG_INF));
  ck_assert_double_nan(s21_tan(S21_NEG_INF));
}
END_TEST

START_TEST(asin_acos_atan_test) {
  ck_assert_double_nan(s21_asin(S21_NAN));
  ck_assert_double_nan(s21_acos(S21_NAN));
  ck_assert_double_nan(s21_atan(S21_NAN));
  ck_assert_double_nan(s21_asin(S21_POS_INF));
  ck_assert_double_nan(s21_acos(S21_POS_INF));
  ck_assert_double_nan(s21_atan(S21_POS_INF));
  ck_assert_double_nan(s21_asin(S21_NEG_INF));
  ck_assert_double_nan(s21_acos(S21_NEG_INF));
  ck_assert_double_eq(atan(-INFINITY), atan(S21_NEG_INF));
  ck_assert_double_nan(s21_asin(4));
  ck_assert_double_nan(s21_acos(7));
  ck_assert_double_nan(s21_asin(-8));
}
END_TEST

Suite *s21_math_suite(void) {
  Suite *suite;

  suite = suite_create("s21_math");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, abs_test_1);
  tcase_add_test(tcase_core, abs_test_2);
  tcase_add_test(tcase_core, acos_test_1);
  tcase_add_test(tcase_core, acos_test_2);
  tcase_add_test(tcase_core, acos_test_3);
  tcase_add_test(tcase_core, acos_test_4);
  tcase_add_test(tcase_core, asin_test_1);
  tcase_add_test(tcase_core, asin_test_2);
  tcase_add_test(tcase_core, atan_test_1);
  tcase_add_test(tcase_core, atan_test_2);
  tcase_add_test(tcase_core, ceil_test);
  tcase_add_test(tcase_core, cos_test_1);
  tcase_add_test(tcase_core, cos_test_2);
  tcase_add_test(tcase_core, exp_test_1);
  tcase_add_test(tcase_core, exp_test_2);
  tcase_add_test(tcase_core, exp_test_3);
  tcase_add_test(tcase_core, exp_test_4);
  tcase_add_test(tcase_core, fabs_test);
  tcase_add_test(tcase_core, floor_test);
  tcase_add_test(tcase_core, fmod_test_1);
  tcase_add_test(tcase_core, fmod_test_2);
  tcase_add_test(tcase_core, log_test_1);
  tcase_add_test(tcase_core, log_test_2);
  tcase_add_test(tcase_core, log_test_3);
  tcase_add_test(tcase_core, log_test_4);
  tcase_add_test(tcase_core, log_test_5);
  tcase_add_test(tcase_core, pow_test_1);
  tcase_add_test(tcase_core, pow_test_2);
  tcase_add_test(tcase_core, pow_test_3);
  tcase_add_test(tcase_core, sin_test_1);
  tcase_add_test(tcase_core, sin_test_2);
  tcase_add_test(tcase_core, sqrt_test_1);
  tcase_add_test(tcase_core, sqrt_test_2);
  tcase_add_test(tcase_core, tan_test_1);
  tcase_add_test(tcase_core, tan_test_2);
  tcase_add_test(tcase_core, sin_cos_tan_test);
  tcase_add_test(tcase_core, asin_acos_atan_test);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_math_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
