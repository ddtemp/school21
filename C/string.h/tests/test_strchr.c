#include "../s21_tests.h"

START_TEST(letter_find_case) {
  char src[] = "testingcase";
  char find = 'a';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(upper_find_case) {
  char src[] = "testingcAse";
  char find = 'A';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(num_find_case) {
  char src[] = "testingcase2";
  char find = '2';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(z_find_case) {
  char src[] = "testingcase";
  char find = 'Z';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(nonum_find_case) {
  char src[] = "testingcase";
  char find = '4';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(empty_case) {
  char src[] = "";
  char find = '4';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");

  tcase_add_test(tc, letter_find_case);
  tcase_add_test(tc, upper_find_case);
  tcase_add_test(tc, num_find_case);
  tcase_add_test(tc, z_find_case);
  tcase_add_test(tc, nonum_find_case);
  tcase_add_test(tc, empty_case);

  suite_add_tcase(s, tc);
  return s;
}