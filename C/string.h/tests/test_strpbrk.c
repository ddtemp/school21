#include "../s21_tests.h"

START_TEST(empty_case) {
  char str1[] = "";
  char str2[] = "";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(one_str_case) {
  char str1[] = "biba";
  char str2[] = "";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(one_str2_case) {
  char str1[] = "";
  char str2[] = "boba";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(standart_case) {
  char str1[] = "biba boba";
  char str2[] = "o";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(base_case) {
  char str1[] = "biba boba";
  char str2[] = "i";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(default_case) {
  char str1[] = "biba boba";
  char str2[] = "b";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(find_X_case) {
  char str1[] = "xxxxxxxxX";
  char str2[] = "X";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(find_zero_case) {
  char str1[] = "xxxxxxxxxxX";
  char str2[] = "\0";

  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *suite_strpbrk(void) {
  Suite *s = suite_create("suite_strpbrk");
  TCase *tc = tcase_create("strpbrk_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, one_str_case);
  tcase_add_test(tc, one_str2_case);
  tcase_add_test(tc, standart_case);
  tcase_add_test(tc, base_case);
  tcase_add_test(tc, default_case);
  tcase_add_test(tc, find_X_case);
  tcase_add_test(tc, find_zero_case);

  suite_add_tcase(s, tc);
  return s;
}