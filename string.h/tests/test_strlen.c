#include "../s21_tests.h"

START_TEST(empty_case) {
  char src[] = "";
  ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(longer_case) {
  char src[] = "fddsjfgdsjfghdsfgsdgfsdhfasdgwgrywefhgvbzxncxasdqeas,c,zpoweqq";
  ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(normal_case) {
  char src[] = "test norm case";
  ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(num_case) {
  char src[] = "123456789012345678901234567890";
  ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(zero_case) {
  char src[] = "pozelo\0-povezlo";
  ck_assert_uint_eq(s21_strlen(src), strlen(src));
}
END_TEST

Suite *suite_strlen(void) {
  Suite *s = suite_create("suite_strlen");
  TCase *tc = tcase_create("strlen_tcase");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, longer_case);
  tcase_add_test(tc, normal_case);
  tcase_add_test(tc, num_case);
  tcase_add_test(tc, zero_case);

  suite_add_tcase(s, tc);
  return s;
}