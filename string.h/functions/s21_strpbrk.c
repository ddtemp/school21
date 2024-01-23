#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  while (*str1 && !flag) {
    for (s21_size_t i = 0; i < s21_strlen(str2); i++) {
      if (*str1 == str2[i]) {
        flag = 1;
        break;
      }
    }
    if (!flag) str1++;
  }
  return flag ? (char *)str1 : S21_NULL;
}
