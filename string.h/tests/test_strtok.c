#include "../s21_tests.h"

START_TEST(empty_case) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(string_case) {
  char src[] = "string";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(case_string) {
  char src[] = "";
  char res[] = "string";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(any_register_case) {
  char src[] = "string";
  char res[] = "sTring";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_case) {
  char src[] = "123456";
  char res[] = "123456";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(long_num_case) {
  char src[] = "123456789";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_long_case) {
  char src[] = "123";
  char res[] = "123456789";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(any_num_case) {
  char src[] = "1234567890";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(caps_letter_num_case) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(num_letter_case) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(standart_case) {
  char src[] = "absD";
  char res[] = "aD";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(random_symbol_case) {
  char src[] = "32fdsgfshjefasuyrasfbdfmaauewyaczvn";
  char res[] = "0987654321";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(caps_case) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(nocaps_case) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(not_match_case) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";

  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(token_string_case) {
  char str1[] = "Aboba++Floppa_! Kotya====!Shleppa";
  char str2[] = "Aboba++Floppa_! Kotya====!Shleppa";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strong_token_case) {
  char str1[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
  char str2[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(unary_delims_case) {
  char str1[] = "verter+vizzinic_absentrc!Gameof_life";
  char str2[] = "verter+vizzinic_absentrc!Gameof_life";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(no_delims_case) {
  char str1[] = "NoChancesNoDelims";
  char str2[] = "NoChancesNoDelims";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    ck_assert_ptr_null(got);
    ck_assert_ptr_null(expected);
  }
}
END_TEST

START_TEST(only_pattern_case) {
  char str1[] = "++++++++";
  char str2[] = "++++++++";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_ptr_null(got);
  ck_assert_ptr_null(expected);
}
END_TEST

START_TEST(strong_uses_case) {
  char str1[] = "Lupa_Pupa_Kuba";
  char str2[] = "Lupa_Pupa_Kuba";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  int i = 5;
  while (i) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);
    i--;

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(even_delims_case) {
  char str1[] = "Lupa++++Pupa++A++++B__V";
  char str2[] = "Lupa++++Pupa++A++++B__V";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(odd_of_delims_case) {
  char str1[] = "Lupa__+Pupa_  Upali";
  char str2[] = "Lupa__+Pupa_  Upali";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(shuffled_delims_case) {
  char str1[] = "Lupa__Pupa_+++sdavali_stringh";
  char str2[] = "Lupa__Pupa_+++sdavali_stringh";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strong_patterns_case) {
  char str1[] = "     Lupa__+ Pu!pa_   meme+";
  char str2[] = "     Lupa__+ Pu!pa_   meme+";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got || expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(mixed_hard_incorrect) {
  char str1[] = "!Alina__ !Sa!sh a____Vanya+Ar!!!tur";
  char str2[] = "!Alina__ !Sa!sh a____Vanya+Ar!!!tur";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got || expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(ultra_patterns_case) {
  char str1[] = "!       A!B!C!D!E!!F!!G";
  char str2[] = "!       A!B!C!D!E!!F!!G";
  const char delims[] = "+_! =";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got || expected) {
    got = s21_strtok(NULL, delims);
    expected = strtok(NULL, delims);

    if (got || expected) {
      ck_assert_str_eq(got, expected);
      ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("suite_strtok");
  TCase *tc = tcase_create("strtok_tc");

  tcase_add_test(tc, empty_case);
  tcase_add_test(tc, string_case);
  tcase_add_test(tc, case_string);
  tcase_add_test(tc, any_register_case);
  tcase_add_test(tc, num_case);
  tcase_add_test(tc, long_num_case);
  tcase_add_test(tc, num_long_case);
  tcase_add_test(tc, any_num_case);
  tcase_add_test(tc, caps_letter_num_case);
  tcase_add_test(tc, num_letter_case);
  tcase_add_test(tc, standart_case);
  tcase_add_test(tc, random_symbol_case);
  tcase_add_test(tc, caps_case);
  tcase_add_test(tc, nocaps_case);
  tcase_add_test(tc, not_match_case);
  tcase_add_test(tc, token_string_case);
  tcase_add_test(tc, strong_token_case);
  tcase_add_test(tc, only_pattern_case);
  tcase_add_test(tc, even_delims_case);
  tcase_add_test(tc, odd_of_delims_case);
  tcase_add_test(tc, shuffled_delims_case);
  tcase_add_test(tc, strong_uses_case);
  tcase_add_test(tc, strong_patterns_case);
  tcase_add_test(tc, mixed_hard_incorrect);
  tcase_add_test(tc, ultra_patterns_case);
  tcase_add_test(tc, unary_delims_case);
  tcase_add_test(tc, no_delims_case);

  suite_add_tcase(s, tc);
  return s;
}