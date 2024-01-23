#include "../s21_string.h"

typedef struct {
  int width;
  int flag_w;
  int flag_minus;
  int count_s;
  int flag_star;
  int flag_plus;
  int number_systems;
  char length;
  char u;
} Flags;

int skip_sym(const char *str, const char *sym);
const char *get_width_(const char *format, Flags *flags);
const char *set_flags(const char *format, Flags *flags);
char set_len(char size, char spec);
const char *set_sys(const char *str, Flags *flags);
const char *integer(char spec, const char *str, void *dest, char size,
                    int *count_success, Flags flags);
const char *unsign(char spec, const char *str, void *arg, char size,
                   int *count_success, Flags flags);
const char *parser_(const char *str, const char *string, const char *format,
                    Flags flags, void *arg, int *count_success);
const char *function_p(const char *str, Flags flags, void *arg, char size,
                       int *count_success, char spec);
char get_char_num_q(char c);
const char *function_d_i(const char *str, Flags flags, long long *num);
const char *function_s(const char *str, Flags flags, void *arg, int *count_res);
const char *function_f(const char *str, Flags flags, void *arg, int *count_res,
                       char size);
const char *func_f(const char *str, Flags flags, long double *num,
                   int *count_res);
int is_nan_or_inf_scan(const char *str, long double *num);

int s21_sscanf(const char *str, const char *format, ...) {
  char specs[] = "diuoxXcsnpfFeEgG%";
  va_list args;
  va_start(args, format);

  int count_succes = -1;
  const char *string = str;
  if (!*str) str = S21_NULL;

  while (*format && str) {
    if (*format == '%') {
      format++;
      Flags flags = {0};
      format = set_flags(format, &flags);
      while (!s21_strchr(specs, *format)) format++;
      void *arg = S21_NULL;
      if (!flags.flag_star) arg = va_arg(args, void *);
      str = parser_(str, string, format, flags, arg, &count_succes);
    } else if (s21_strchr(" \t\n\b\r", *format)) {
      str += skip_sym(str, " \t\n\b\r");
    } else if (*str == *format) {
      str++;
    } else
      break;
    format++;
  }
  va_end(args);
  return count_succes;
}

// skip spaces
int skip_sym(const char *str, const char *sym) {
  int i = 0;
  while (s21_strchr(sym, *str) && *str) {
    str++;
    i++;
  }
  return i;
}

// set flags for format specificators
const char *set_flags(const char *format, Flags *flags) {
  flags->flag_w = 1;
  flags->number_systems = 10;
  flags->flag_minus = 1;
  if (*format == '*') {
    flags->flag_star = 1;
    format++;
  }
  format = get_width_(format, flags);
  if (!flags->width) flags->width = INT_MAX;
  return format;
}

// parses the format string and extracts
const char *get_width_(const char *format, Flags *flags) {
  flags->width = 0;
  while (format) {
    if ('0' <= *format && *format <= '9' &&
        flags->width < (INT_MAX - *format + 48) / 10)
      flags->width = (flags->width) * 10 + *format - 48;
    else
      break;
    format++;
  }
  return format;
}

// parse specificators
const char *parser_(const char *str, const char *string, const char *format,
                    Flags flags, void *arg, int *count_success) {
  char spec = *format;
  const char *start = str + skip_sym(str, " \t\n\r\b");
  if (*count_success < 0 && *start != '\0') *count_success = 0;
  if ((*format == 'd' || *format == 'i') && *start != '\0') {
    str = integer(spec, start, arg, *(format - 1), count_success, flags);
  } else if ((*format == 'u' || *format == 'o' || *format == 'x' ||
              *format == 'X') &&
             *start != '\0') {
    if (*format == 'o')
      flags.number_systems = 8;
    else if (*format == 'x' || *format == 'X')
      flags.number_systems = 16;
    str = unsign(spec, start, arg, *(format - 1), count_success, flags);
  } else if (*format == 'c') {
    if (flags.flag_star) {
      str++;
    } else {
      *(char *)arg = *str;
      *count_success += 1;
      str++;
    }
  } else if (*format == 's' && *start != '\0') {
    str = function_s(start, flags, arg, count_success);
  } else if (*format == 'n') {
    int *n = (int *)arg;
    if (n) *n = str - string;
  } else if (*format == 'p' && *start != '\0') {
    str = function_p(start, flags, arg, *(format - 1), count_success, spec);
  } else if ((*format == 'f' || *format == 'F' || *format == 'e' ||
              *format == 'E' || *format == 'g' || *format == 'G') &&
             *start != '\0') {
    str = function_f(str, flags, arg, count_success, *(format - 1));
  } else
    str = S21_NULL;
  return str;
}

// for integer type
const char *integer(char spec, const char *str, void *dest, char size,
                    int *count_success, Flags flags) {
  flags.length = set_len(size, spec);
  if (spec == 'i') str = set_sys(str, &flags);
  long long num;
  str = function_d_i(str, flags, &num);
  if (dest && str) {
    s21_memcpy(dest, &num, flags.length);
    *count_success += 1;
  }
  return str;
}

// get len
char set_len(char size, char spec) {
  char res = 0;
  if (spec == 'i' || spec == 'u' || spec == 'd') {
    if (size == 'l')
      res = sizeof(long long);
    else if (size == 'h')
      res = sizeof(short);
    else
      res = sizeof(int);
  }
  return res;
}

// сисема счисления
const char *set_sys(const char *str, Flags *flags) {
  str += skip_sym(str, " \t\b\n\r");
  if (*str == '0') flags->number_systems = 8;
  if (*(str + 1) == 'x' || *(str + 1) == 'X') flags->number_systems = 16;
  return str;
}

// specificators %d and %i
const char *function_d_i(const char *str, Flags flags, long long *num) {
  int n = 0;
  const char *s = str;
  const char *res = "1";
  if (!(isdigit(*str))) {
    if (*str == '-') {
      str++;
      if (get_char_num_q(*str) != '?') {
        flags.flag_minus = -1;
      } else
        res = S21_NULL;
    } else if (!(isdigit(*str)) && *str == '+') {
      flags.flag_plus = 1;
      str++;
      if (get_char_num_q(*str) == '?') res = S21_NULL;
    }
  }
  if (res != S21_NULL && get_char_num_q(*str) != '?' &&
      get_char_num_q(*str) < flags.number_systems && str - s < flags.width) {
    *num = 0;
  } else
    res = S21_NULL;
  if ((s21_strchr(str, 'x') || s21_strchr(str, 'X')) &&
      flags.number_systems == 16 && res != S21_NULL)
    str += 2;
  while (*str != ' ' && *str != '\n' && *str != '\t' && str - s < flags.width) {
    if (res == S21_NULL) break;
    n = get_char_num_q(*str);
    if (n < flags.number_systems && n != '?')
      *num = *num * flags.number_systems + n * flags.flag_minus;
    else
      break;
    str++;
  }
  if (res != S21_NULL) res = str;
  return res;
}

// transform char to int
char get_char_num_q(char c) {
  char flag = '?';
  if (c == 'a' || c == 'A')
    flag = 10;
  else if (c == 'b' || c == 'B')
    flag = 11;
  else if (c == 'c' || c == 'C')
    flag = 12;
  else if (c == 'd' || c == 'D')
    flag = 13;
  else if (c == 'e' || c == 'E')
    flag = 14;
  else if (c == 'f' || c == 'F')
    flag = 15;
  if ('0' <= c && c <= '9') flag = c - 48;
  return flag;
}

// целое число без знака
const char *unsign(char spec, const char *str, void *arg, char size,
                   int *count_success, Flags flags) {
  spec = 'u';
  flags.length = set_len(size, spec);
  unsigned long long num;
  str = function_d_i(str, flags, (long long *)&num);
  if (arg && str) {
    s21_memcpy(arg, &num, flags.length);
    *count_success += 1;
  }
  return str;
}

// skip spaces
const char *function_s(const char *str, Flags flags, void *arg,
                       int *count_res) {
  str += skip_sym(str, " \t\n\r\b");
  int skip = 0;
  if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' ||
      *str == '\b')
    skip = 1;
  int i = 0;
  while ((*str && !skip && i < flags.width) && flags.flag_w > 0) {
    if (arg) *((char *)arg + i) = *str;
    str++;
    if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' ||
        *str == '\b')
      skip = 1;
    i++;
  }
  if (arg) {
    *((char *)arg + i) = '\0';
    *count_res += 1;
  }
  return str;
}

const char *function_p(const char *str, Flags flags, void *arg, char size,
                       int *count_success, char spec) {
  spec = 'u';
  flags.length = set_len(size, spec);
  flags.number_systems = 16;
  long long num;
  str = function_d_i(str, flags, (long long *)&num);
  if (arg && str) {
    *(long long *)arg = num;
    *count_success += 1;
  }
  return str;
}

const char *function_f(const char *str, Flags flags, void *arg, int *count_res,
                       char size) {
  long double num;
  str = func_f(str, flags, &num, count_res);
  if (arg && str != S21_NULL) {
    if (size == 'L')
      *(long double *)arg = (long double)num;
    else if (size == 'l')
      *(double *)arg = (double)num;
    else
      *(float *)arg = (float)num;
  }
  return str;
}

// analyze float number
const char *func_f(const char *str, Flags flags, long double *num,
                   int *count_res) {
  long n = 0;
  long long dot = 0;
  const char *s = str;
  const char *res = "1";
  int check = is_nan_or_inf_scan(str, num);
  if (check) str += check;
  if (!(isdigit(*str)) && !check) {
    if (*str == '-') {
      str++;
      if (get_char_num_q(*str) != '?') {
        flags.flag_minus = -1;
      } else
        res = S21_NULL;
    } else if (!(isdigit(*str)) && *str == '+') {
      flags.flag_plus = 1;
      str++;
      if (get_char_num_q(*str) == '?') res = S21_NULL;
    }
  }
  if (res != S21_NULL && get_char_num_q(*str) != '?' &&
      get_char_num_q(*str) < flags.number_systems && str - s < flags.width &&
      !check) {
    *num = 0;
  } else {
    res = S21_NULL;
  }
  if (*str == '.') *num = 0;
  while (*str != ' ' && *str != '\n' && *str != '\t' && str - s < flags.width) {
    if (res == S21_NULL || check) break;
    n = get_char_num_q(*str);
    if (isdigit(*str)) {
      if (dot == 0) {
        *num = *num * flags.number_systems + n * flags.flag_minus;
      } else {
        *num = *num + n * flags.flag_minus / pow(10., dot++);
      }
    } else if (*str == '.' && !check) {
      dot++;
    } else
      break;
    str++;
  }
  if (*str == 'e' || *str == 'E') {
    str++;
    str = function_d_i(str, flags, &dot);
    *num = *num * pow(10., dot);
  }
  if (res != S21_NULL || check) *count_res += 1;
  return str;
}

// checking in nan or infinity numbers
int is_nan_or_inf_scan(const char *str, long double *num) {
  int flag = 0;
  if ((*str == 'n' || *str == 'N') &&
      (*(str + 1) == 'a' || *(str + 1) == 'A') &&
      (*(str + 2) == 'n' || *(str + 2) == 'N')) {
    flag = 3;
    *num = NAN;
  } else if ((*str == 'i' || *str == 'I') &&
             (*(str + 1) == 'n' || *(str + 1) == 'N') &&
             (*(str + 2) == 'f' || *(str + 2) == 'F')) {
    flag = 3;
    *num = INFINITY;
  } else if ((*str == '-') && (*(str + 1) == 'i' || *(str + 1) == 'I') &&
             (*(str + 2) == 'n' || *(str + 2) == 'N') &&
             (*(str + 3) == 'f' || *(str + 3) == 'F')) {
    flag = 4;
    *num = -INFINITY;
  }
  return flag;
}
