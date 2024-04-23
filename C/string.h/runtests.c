#include "s21_tests.h"
int main(void) {
  run_tests();
  return 0;
}
void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 1) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
void run_tests(void) {
  Suite *list_cases[] = {
      suite_strlen(), suite_strncat(),  suite_strncpy(),  suite_strncmp(),
      suite_memcpy(), suite_memcmp(),   suite_memset(),   suite_memchr(),
      suite_strchr(), suite_strcspn(),  suite_strpbrk(),  suite_strrchr(),
      suite_strstr(), suite_to_lower(), suite_to_upper(), suite_strtok(),
      suite_insert(), suite_trim(),     suite_sprintf(),  suite_strerror(),
      suite_sscanf(), S21_NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != S21_NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
  printf("\n");
}
