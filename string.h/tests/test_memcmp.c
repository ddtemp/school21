#include "../s21_tests.h"

START_TEST(zero_case) {
  char str1[] = "amogus";
  char str2[] = "amogus";
  int n = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(first_byte_case) {
  char str1[] = "amogus";
  char str2[] = "amogus";
  int n = 3;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(letter_case) {
  char str1[] = "amogus";
  char str2[] = "Amogus";
  int n = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(zero_num_case) {
  char str1[] = "1";
  char str2[] = "1";
  int n = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(first_num_case) {
  char str1[] = "1";
  char str2[] = "1234";
  int n = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(bytes_num_case) {
  char str1[] = "1234";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(bytes_longnum_case) {
  char str1[] = "13";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(longnum_bytes_case) {
  char str1[] = "134567";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(eq_str_case) {
  char str1[] =
      "661231724216314dfsdfgsdhjfgasjdhf3641289eausdfghsa 1273412e4ashdfasdfbb";
  char str2[] =
      "661231724216314dfsdfgsdhjfgasjdhf3641289eausdfghsa 1273412e4ashdfasdfbb";
  int n = 71;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(n_eq_str_case) {
  char str1[] =
      "661231724216314dfsdfgsdhjfgasjdhf3641289eausdfghsa 1273412e4ashdfasdfbB";
  char str2[] =
      "661231724216314dfsdfgsdhjfgasjdhf3641289eausdfghsa 1273412e4ashdfasdfbB";
  int n = 71;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

Suite *suite_memcmp(void) {
  Suite *s = suite_create("suite_memcmp");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, zero_case);
  tcase_add_test(tc, first_byte_case);
  tcase_add_test(tc, letter_case);
  tcase_add_test(tc, zero_num_case);
  tcase_add_test(tc, first_num_case);
  tcase_add_test(tc, bytes_num_case);
  tcase_add_test(tc, bytes_longnum_case);
  tcase_add_test(tc, longnum_bytes_case);
  tcase_add_test(tc, eq_str_case);
  tcase_add_test(tc, n_eq_str_case);

  suite_add_tcase(s, tc);
  return s;
}