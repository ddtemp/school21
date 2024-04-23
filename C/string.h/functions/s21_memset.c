#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *strPointer = (unsigned char *)str;
  while (n--) {
    *strPointer++ = (unsigned char)c;
  }
  return str;
}
