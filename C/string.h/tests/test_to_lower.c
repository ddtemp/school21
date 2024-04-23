#include "../s21_tests.h"

START_TEST(numbers_case) {
  char str[] = "0123456789Q";
  char expected[] = "0123456789q";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(start_case) {
  char str[] = "Space created";
  char expected[] = "space created";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(empty_case) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(space_case) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *s = suite_create("suite_to_lower");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, numbers_case);
  tcase_add_test(tc, start_case);
  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, space_case);

  suite_add_tcase(s, tc);
  return s;
}