#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  unsigned int firstStrLength = s21_strlen(str1);
  unsigned int secondStrLength = s21_strlen(str2);
  unsigned int i = 0;
  int exit = 0;

  for (; i < firstStrLength;) {
    if (exit == 1) {
      break;
    } else {
      for (unsigned int j = 0; j < secondStrLength; j++) {
        if (str1[i] == str2[j]) {
          exit = 1;
        }
      }
    }
    if (exit == 0) {
      i++;
    }
  }

  return i;
}
