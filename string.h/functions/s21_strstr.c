#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t needleLength = s21_strlen(needle);
  int flag = 1;
  if (needleLength) {
    flag = 0;
    s21_size_t haystackLength = s21_strlen(haystack);
    while (haystackLength-- >= needleLength) {
      if (!s21_memcmp(haystack, needle, needleLength)) {
        flag = 1;
        break;
      }
      haystack++;
    }
  }
  return flag ? (char *)haystack : S21_NULL;
}
