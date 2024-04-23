#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  char *output = S21_NULL;
  if (str) {
    output = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    for (int i = 0; str[i]; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        output[i] = str[i] + 32;
      } else {
        output[i] = str[i];
      }
    }
  }
  return output;
}
