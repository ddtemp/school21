#include "../s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int i;
  int length;
  i = 0;
  length = 0;
  while (dest[i] != '\0') {
    length++;
    i++;
  }
  i = 0;
  while (src[i] != '\0') {
    dest[length + i] = src[i];
    i++;
  }
  dest[length + i] = '\0';
  return (dest);
}
