#include "../s21_tests.h"

START_TEST(standart_case) {
  char str[] = "nice work";
  char expected[] = "NICE WORK";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(oneword_case) {
  char str[] = "empty";
  char expected[] = "EMPTY";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(numbers_case) {
  char str[] = "2+2*2";
  char expected[] = "2+2*2";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(space_case) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(empty_case) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite_to_upper");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, standart_case);
  tcase_add_test(tc, oneword_case);
  tcase_add_test(tc, numbers_case);
  tcase_add_test(tc, space_case);
  tcase_add_test(tc, empty_case);

  suite_add_tcase(s, tc);
  return s;
}