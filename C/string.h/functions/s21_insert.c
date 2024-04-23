#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (!((str == S21_NULL && src == S21_NULL) ||
        start_index > s21_strlen(src))) {
    result = (char *)malloc(sizeof(char) * (s21_strlen(str) + s21_strlen(src)));
    for (s21_size_t i = 0; i < start_index; i++) {
      result[i] = src[i];
    }
    for (s21_size_t i = start_index; i < start_index + s21_strlen(str); i++) {
      result[i] = str[i - start_index];
    }
    for (s21_size_t i = start_index + s21_strlen(str);
         i < s21_strlen(str) + s21_strlen(src); i++) {
      result[i] = src[i - s21_strlen(str)];
    }
    result[s21_strlen(str) + s21_strlen(src)] = '\0';
  }
  return result;
}
