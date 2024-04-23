#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *destPointer = (unsigned char *)dest;
  const unsigned char *srcPointer = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    destPointer[i] = srcPointer[i];
  }
  return dest;
}
