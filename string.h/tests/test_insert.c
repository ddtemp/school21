#include "../s21_tests.h"

START_TEST(insert_mid_case) {
  char str[] = "School";
  char src[] = "I love my . This is the best place in the world";
  s21_size_t index = 10;
  char expected[] = "I love my School. This is the best place in the world";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_start_case) {
  char str[] = "Hello, ";
  char src[] = "world!";
  s21_size_t index = 0;
  char expected[] = "Hello, world!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(null_case) {
  char *src = S21_NULL;
  char *str = S21_NULL;
  s21_size_t index = 100;
  char *expected = S21_NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_end_case) {
  char str[] = "Monkey";
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space Monkey ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_str_null) {
  char *str = NULL;
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space  ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, insert_mid_case);
  tcase_add_test(tc, insert_start_case);
  tcase_add_test(tc, null_case);
  tcase_add_test(tc, insert_end_case);
  tcase_add_test(tc, insert_str_null);

  suite_add_tcase(s, tc);
  return s;
}
