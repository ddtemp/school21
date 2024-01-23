#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  c = (char)c;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      return (char *)&str[i];
    }
  }

  return S21_NULL;
}
