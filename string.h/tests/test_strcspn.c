#include "../s21_tests.h"

START_TEST(empty_case) {
  char src[] = "";
  char res[] = "";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(res_empty_case) {
  char src[] = "smash";
  char res[] = "";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(src_empty_case) {
  char src[] = "";
  char res[] = "smash";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(any_register_case) {
  char src[] = "smash";
  char res[] = "smash";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(num_case) {
  char src[] = "123";
  char res[] = "123";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(long_num_case) {
  char src[] = "12345";
  char res[] = "123";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(num_long_case) {
  char src[] = "123";
  char res[] = "12345";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(any_num_case) {
  char src[] = "1234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(num_letter_case) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(nocaps_letter_num_case) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(standart_test) {
  char src[] = "absD";
  char res[] = "aD";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(any_char_case) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(upper_letter_case) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(lower_letter_case) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(nuniq_symb_case) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";

  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

Suite *suite_strcspn(void) {
  Suite *s = suite_create("suite_strcspn");
  TCase *tc = tcase_create("strcspn_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, res_empty_case);
  tcase_add_test(tc, src_empty_case);
  tcase_add_test(tc, any_register_case);
  tcase_add_test(tc, num_case);
  tcase_add_test(tc, long_num_case);
  tcase_add_test(tc, num_long_case);
  tcase_add_test(tc, any_num_case);
  tcase_add_test(tc, num_letter_case);
  tcase_add_test(tc, nocaps_letter_num_case);
  tcase_add_test(tc, standart_test);
  tcase_add_test(tc, any_char_case);
  tcase_add_test(tc, upper_letter_case);
  tcase_add_test(tc, lower_letter_case);
  tcase_add_test(tc, nuniq_symb_case);

  suite_add_tcase(s, tc);
  return s;
}