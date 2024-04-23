#include "../s21_tests.h"

START_TEST(empty_case) {
  char str1[] = "";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(one_str_case) {
  char str1[] = "biba";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(one_str2_case) {
  char str1[] = "";
  char str2 = 'b';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(standart_case) {
  char str1[] = "biba boba";
  char str2 = 'b';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(base_case) {
  char str1[] = "biba i boba";
  char str2 = 'i';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(default_case) {
  char str1[] = "biba boba";
  char str2 = 'a';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(find_X_case) {
  char str1[] = "xxXxxxxxXxxxx";
  char str2 = 'X';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(find_zero_case) {
  char str1[] = "123456789";
  char str2 = '0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

Suite *suite_strrchr(void) {
  Suite *s = suite_create("suite_strrchr");
  TCase *tc = tcase_create("strrchr_tc");

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