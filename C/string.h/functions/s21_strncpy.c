#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t count = 0;

  while (count < n && src[count] && src && dest) {
    dest[count] = src[count];
    count++;
  }
  while (count < n && dest && src) {
    dest[count] = '\0';
    count++;
  }

  return dest;
}
