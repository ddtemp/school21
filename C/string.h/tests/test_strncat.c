#include "../s21_tests.h"

START_TEST(empty_case) {
  char src[] = "";
  char res[] = "";
  char expected[] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_case) {
  char src[] = "abosal";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(main_empty) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(bd_amogus) {
  char src[] = "amogus";
  char res[10] = "bd";
  char expected[10] = "bd";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(string) {
  char src[] = "abosal";
  char res[25] = "koleka";
  char expected[25] = "koleka";
  s21_size_t n_byte = 6;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(caps_string_case) {
  char src[] = "STRINGH";
  char res[25] = "STRINGH";
  char expected[25] = "STRINGH";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(caps_string2_case) {
  char src[] = "STRINGH";
  char res[25] = "STRINGH";
  char expected[25] = "STRINGH";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(caps_string3_case) {
  char src[] = "STRINGH";
  char res[25] = "STRINGH";
  char expected[25] = "STRINGH";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(caps_string4_case) {
  char src[] = "STRINGH";
  char res[25] = "STRINGH";
  char expected[25] = "STRINGH";
  s21_size_t n_byte = 10;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_char_case) {
  char src[] = "\0";
  char res[25] = "STRINGH";
  char expected[25] = "STRINGH";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("suite_strncat");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, zero_case);
  tcase_add_test(tc, main_empty);
  tcase_add_test(tc, bd_amogus);
  tcase_add_test(tc, string);
  tcase_add_test(tc, caps_string_case);
  tcase_add_test(tc, caps_string2_case);
  tcase_add_test(tc, caps_string3_case);
  tcase_add_test(tc, caps_string4_case);
  tcase_add_test(tc, zero_char_case);

  suite_add_tcase(s, tc);
  return s;
}