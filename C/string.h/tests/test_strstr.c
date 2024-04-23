#include "../s21_tests.h"

START_TEST(empty_case) {
  char haystack[] = "";
  char needle[] = "";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(empty_str1_case) {
  char haystack[] = "";
  char needle[] = "asdfgadsgadstardsfsda";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(empty_str2_case) {
  char haystack[] = "safQhilufas7MaSef2345wknwefnkjHawe2fhilu";
  char needle[] = "";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(base_case) {
  char haystack[] = "You are cute!";
  char needle[] = "cute";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(n_eq_case) {
  char haystack[] = "not_equal_test_case!";
  char needle[] = "word";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(letter_upper_case) {
  char haystack[] = "pEpegE_mEmE";
  char needle[] = "pepEGa_mEme";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(more_eq_case) {
  char haystack[] = "DA DA DA";
  char needle[] = "DA";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(eq_end_case) {
  char haystack[] = "22 321 123";
  char needle[] = "123";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(char_case) {
  char haystack[] = "1";
  char needle[] = "1";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(char_str2_case) {
  char haystack[] =
      "drjkhagfdsfgyadsufh4dquy3ct4g5hq3jhdfghjaerga dshfgakjdfhdquc drash";
  char needle[] = " ";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(char_str1_case) {
  char haystack[] = "!";
  char needle[] = "adsgadsjhfadsurgadshrfahsj!";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite_strstr");
  TCase *tc = tcase_create("strstr_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, empty_str1_case);
  tcase_add_test(tc, empty_str2_case);
  tcase_add_test(tc, base_case);
  tcase_add_test(tc, n_eq_case);
  tcase_add_test(tc, letter_upper_case);
  tcase_add_test(tc, more_eq_case);
  tcase_add_test(tc, eq_end_case);
  tcase_add_test(tc, char_case);
  tcase_add_test(tc, char_str2_case);
  tcase_add_test(tc, char_str1_case);

  suite_add_tcase(s, tc);
  return s;
}