#include "../s21_tests.h"

START_TEST(empty_case) {
  char src[] = "";
  char res[] = "";
  char exp[] = "";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(nobyte_case) {
  char src[] = "123";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(empty_src_case) {
  char src[] = "";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(byte_case) {
  char src[] = "123";
  char res[5] = "123";
  char exp[5] = "123";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(bytes_case) {
  char src[] = "123";
  char res[7] = "123";
  char exp[7] = "123";
  s21_size_t n_byte = 2;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(string_case) {
  char src[] = "Str1ng";
  char res[7 + 7] = "Str1ng";
  char exp[7 + 7] = "Str1ng";
  s21_size_t n_byte = 7;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite_strncpy");
  TCase *tc = tcase_create("strncpy_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, nobyte_case);
  tcase_add_test(tc, empty_src_case);
  tcase_add_test(tc, byte_case);
  tcase_add_test(tc, bytes_case);
  tcase_add_test(tc, string_case);

  suite_add_tcase(s, tc);
  return s;
}