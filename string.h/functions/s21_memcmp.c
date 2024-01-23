#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++, s1++, s2++) {
    if (*s1 != *s2) {
      return (int)*s1 - (int)*s2;
    }
  }

  return 0;
}
