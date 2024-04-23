#include "../s21_tests.h"

START_TEST(standart_case) {
  char res[] = "amogus";
  char expected[] = "amogus";
  char replace = 'g';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(zero_case) {
  char res[] = "amogus";
  char expected[] = "amogus";
  char replace = 'g';
  s21_size_t n_byte = 0;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST
START_TEST(empty_case) {
  char res[] = "";
  char expected[] = "";
  char replace = '\0';
  s21_size_t n_byte = 0;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(replace_symbol_case) {
  char res[] = "amogus";
  char expected[] = "amogus";
  char replace = 'A';
  s21_size_t n_byte = 3;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(replace_number_case) {
  char res[] = "a1moguS";
  char expected[] = "a1moguS";
  char replace = '1';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(long_string_case) {
  char res[] =
      "a1gkjthaycbrvarcmkldjngbkuydscfxgzhku rweaiuarc aeirnabi "
      "rcecraoCNBRANMLXJHsdgfs";
  char expected[] =
      "a1gkjthaycbrvarcmkldjngbkuydscfxgzhku rweaiuarc aeirnabi "
      "rcecraoCNBRANMLXJHsdgfs";
  char replace = '1';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *suite_memset(void) {
  Suite *s = suite_create("suite_memset");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, standart_case);
  tcase_add_test(tc, zero_case);
  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, replace_symbol_case);
  tcase_add_test(tc, replace_number_case);
  tcase_add_test(tc, long_string_case);

  suite_add_tcase(s, tc);
  return s;
}