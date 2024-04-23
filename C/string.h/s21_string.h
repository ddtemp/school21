#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_NULL ((void *)0)
typedef unsigned long long s21_size_t;

#define is_flag(ch) \
  ((ch) == '-' || (ch) == '+' || (ch) == ' ' || (ch) == '#' || (ch) == '0')

#define is_len_opt(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_octal_digit(ch) ((ch) >= '0' && (ch) <= '7')

#define is_hex_digit(ch)                                                      \
  (((ch) >= '0' && (ch) <= '9') || (ch) == 'a' || (ch) == 'b' ||              \
   (ch) == 'c' || (ch) == 'd' || (ch) == 'e' || (ch) == 'f' || (ch) == 'A' || \
   (ch) == 'B' || (ch) == 'C' || (ch) == 'D' || (ch) == 'E' || (ch) == 'F')

#define is_specifier(ch)                                                      \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'f' || (ch) == 's' || \
   (ch) == 'u' || (ch) == '%' || (ch) == 'g' || (ch) == 'G' || (ch) == 'e' || \
   (ch) == 'E' || (ch) == 'x' || (ch) == 'X' || (ch) == 'o' || (ch) == 'n' || \
   (ch) == 'p')

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);

char *s21_strcat(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);
s21_size_t s21_strspn(const char *str1, const char *str2);

int s21_sscanf(const char *str, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif  // S21_STRING_H
