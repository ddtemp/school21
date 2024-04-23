#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *charPointer = (const unsigned char *)str;

  while (n-- > 0) {
    if (*charPointer == (unsigned char)c) {
      return (void *)charPointer;
    }
    charPointer++;
  }

  return S21_NULL;
}
