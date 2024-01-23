#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t srcIndex = 0;
  s21_size_t destLength = s21_strlen(dest);

  while (srcIndex < n && src[srcIndex]) {
    dest[destLength + srcIndex] = src[srcIndex];
    srcIndex++;
  }
  dest[destLength + srcIndex] = '\0';
  return dest;
}
