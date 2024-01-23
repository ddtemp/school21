#include "../s21_tests.h"

START_TEST(base_case) {
  char src[] = "i love memcmp";
  s21_size_t kByte = 12;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_case) {
  char src[] = "amogus";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(empty_case) {
  char src[] = "";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_str_case) {
  char src[] = "I not hate memcmp";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(zero_num_case) {
  char src[] = "123";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(byte_str_case) {
  char src[] = "you shell not pass";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(byte_str_let_case) {
  char src[] = "Zboba";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(byte_num_case) {
  char src[] = "09";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_str_case) {
  char src[] = "testtesttesttesttest testtest";
  s21_size_t kByte = 28;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_str_let_case) {
  char src[] = "asgjhagdshjfgahsdghbdsjhrgkur DddBBB";
  s21_size_t kByte = 36;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_strnum_case) {
  char src[] = "gsdkjfkghadshjtgdashkfndshfg341fsdjhfghsdjfrghqsdgsra";
  s21_size_t kByte = 53;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(long_strnumch_case) {
  char src[] =
      "|||////_-//:!,....gsdkjfkghadshjtgdashkfndshfg341sdjhfghsdjfrghqsdgsra";
  s21_size_t kByte = 71;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

Suite *suite_memcpy(void) {
  Suite *s = suite_create("suite_memcpy");
  TCase *tc = tcase_create("memcpy_tc");

  tcase_add_test(tc, base_case);
  tcase_add_test(tc, zero_case);
  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, zero_str_case);
  tcase_add_test(tc, zero_num_case);
  tcase_add_test(tc, byte_str_case);
  tcase_add_test(tc, byte_str_let_case);
  tcase_add_test(tc, byte_num_case);
  tcase_add_test(tc, long_str_case);
  tcase_add_test(tc, long_str_let_case);
  tcase_add_test(tc, long_strnum_case);
  tcase_add_test(tc, long_strnumch_case);

  suite_add_tcase(s, tc);
  return s;
}