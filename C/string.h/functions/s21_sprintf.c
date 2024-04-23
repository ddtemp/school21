#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

typedef struct format {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int flag_error;
  char len;
  char spec;
  int width;
  int precision;
} s_format;

static void s21_set_flag(s_format *options, const char *format);
static char *s21_set_specifiers(char *str, s21_size_t *str_len,
                                s_format *options, va_list *args);
static char *s21_str_to_int(const char *format, int *number, va_list *args);
static char *s21_reverse_str(char *str);
static long double s21_round(long double x, int precision);

static char *s21_c_specifier(char *str, va_list *args, s_format *options);
static char *s21_d_specifier(char *str, va_list *args, s_format *options);
static char *s21_e_specifier(char *str, va_list *args, s_format *options);
static char *s21_f_specifier(char *str, va_list *args, s_format *options);
static char *s21_g_specifier(char *str, va_list *args, s_format *options);
static char *s21_o_specifier(char *str, va_list *args, s_format *options);
static char *s21_s_specifier(char *str, va_list *args, s_format *options);
static char *s21_u_specifier(char *str, va_list *args, s_format *options);
static char *s21_x_specifier(char *str, va_list *args, s_format *options);
static char *s21_p_specifier(char *str, va_list *args, s_format *options);
static void s21_n_specifier(s21_size_t const *str_len, va_list *args);
static char *s21_percent_specifier(char *str, s_format *options);

static char *s21_wch_to_str(char *str, wchar_t *wstr, s21_size_t len);
static char *s21_lf_to_str(char *str, long double number, s_format *options);
static char *s21_le_to_str(char *str, long double number, s_format *options);
static char *s21_lg_to_str(char *str, long double number, s_format *options);
static char *s21_ll_to_str(char *str, long long number);
static char *s21_ul_to_str(char *str, unsigned long long number);
static char *s21_ol_to_str(char *str, unsigned long long number, int prefix);
static char *s21_hl_to_str(char *str, unsigned long long number,
                           s_format *options);
static char *s21_ld_to_str(char *str, long double number, s_format *options);
static char *s21_d_class_to_str(char *str, long double x, int precision);

static char *s21_lf_width_flag(char *str, s_format *options);
static char *s21_ll_width_flag(char *str, s_format *options);
static char *s21_sign_flag(char *str, s_format *options);
static char *s21_precision(char *str, s_format *options);

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  s21_size_t i = 0, flag = 0, error = 0;
  char *str_start = str;
  str = s21_strcpy(str, "");
  while (*format && error == 0) {
    s_format options = {0, 0, 0, 0, 0, 0, 0, 0, -1, -1};
    if (*format == '%') {
      flag = 1;
      format++;
    } else {
      str[i++] = *(format++);
      str[i] = '\0';
    }

    if (flag == 1 && is_flag(*format))
      while (is_flag(*format)) s21_set_flag(&options, format++);

    if (flag == 1 && (is_digit(*format) || *format == '*'))
      format = s21_str_to_int(format, &options.width, &args);

    if (flag == 1 && *format == '.') {
      options.precision = 0;
      format = s21_str_to_int(++format, &options.precision, &args);
    }

    if (flag == 1 && is_len_opt(*format)) options.len = *(format++);

    if (flag == 1 && is_specifier(*format)) options.spec = *(format++);

    if (flag == 1) {
      str = s21_set_specifiers(str, &i, &options, &args);
      error = options.flag_error;
    }
    flag = 0;
  }
  va_end(args);
  if (error != 0) *str_start = '\0';
  return error == 0 ? (int)s21_strlen(str) : -1;
}

static void s21_set_flag(s_format *options, const char *format) {
  switch (*format) {
    case '-':
      options->minus = 1;
      break;
    case '+':
      options->plus = 1;
      break;
    case ' ':
      options->space = 1;
      break;
    case '#':
      options->sharp = 1;
      break;
    case '0':
      options->zero = 1;
      break;
  }
}

static char *s21_set_specifiers(char *str, s21_size_t *str_len,
                                s_format *options, va_list *args) {
  char *temp_str = S21_NULL;
  temp_str = calloc(1000 + options->width + 2, sizeof(char));
  if (temp_str != S21_NULL) {
    switch (options->spec) {
      case 'd':
      case 'i':
        s21_d_specifier(temp_str, args, options);
        break;
      case 'o':
        s21_o_specifier(temp_str, args, options);
        break;
      case 'u':
        s21_u_specifier(temp_str, args, options);
        break;
      case 'x':
      case 'X':
        s21_x_specifier(temp_str, args, options);
        break;
      case 'e':
      case 'E':
        s21_e_specifier(temp_str, args, options);
        break;
      case 'f':
        s21_f_specifier(temp_str, args, options);
        break;
      case 'g':
      case 'G':
        s21_g_specifier(temp_str, args, options);
        break;
      case 'c':
        s21_c_specifier(temp_str, args, options);
        break;
      case 's':
        s21_s_specifier(temp_str, args, options);
        break;
      case 'p':
        s21_p_specifier(temp_str, args, options);
        break;
      case 'n':
        s21_n_specifier(str_len, args);
        break;
      case '%':
        s21_percent_specifier(temp_str, options);
        break;
    }
    s21_strcat(str, temp_str);
    free(temp_str);
    *str_len = s21_strlen(str);
  }
  return str;
}

static void s21_n_specifier(s21_size_t const *str_len, va_list *args) {
  int *p = va_arg(*args, int *);
  *p = (int)*str_len;
}

static char *s21_percent_specifier(char *str, s_format *options) {
  options->precision = 0;
  s21_strcat(str, "%");
  s21_precision(str, options);
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_p_specifier(char *str, va_list *args, s_format *options) {
  int width = options->width < 15 ? 15 : options->width;
  char *str_start = S21_NULL;
  str_start = str;
  int *p = va_arg(*args, int *);
  char buf[4] = "x0";
  if (p == S21_NULL) {
    s21_strcpy(buf, "0x0");
  }

  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((s21_size_t)j) >> 4), k++) {
    unsigned int dig = ((s21_size_t)j) % 0x10;
    if (dig < 10 && options->spec == 'p')
      *(str_start++) = (char)('0' + dig);
    else
      *(str_start++) = (char)('a' + (dig - 10));
  }
  *str_start = '\0';
  s21_strcat(str, buf);
  s21_reverse_str(str);
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_f_specifier(char *str, va_list *args, s_format *options) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (options->len) {
    case 'l':
      d_number = (double)va_arg(*args, double);
      s21_lf_to_str(str, d_number, options);
      break;
    case 'L':
      ld_number = va_arg(*args, long double);
      s21_lf_to_str(str, ld_number, options);
      break;
    default:
      d_number = va_arg(*args, double);
      f_number = d_number;
      s21_lf_to_str(str, f_number, options);
  }
  s21_sign_flag(str, options);
  s21_lf_width_flag(str, options);
  return str;
}

static char *s21_e_specifier(char *str, va_list *args, s_format *options) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (options->len) {
    case 'l':
      d_number = (double)va_arg(*args, double);
      s21_le_to_str(str, d_number, options);
      break;
    case 'L':
      ld_number = va_arg(*args, long double);
      s21_le_to_str(str, ld_number, options);
      break;
    default:
      d_number = va_arg(*args, double);
      f_number = d_number;
      s21_le_to_str(str, f_number, options);
  }
  s21_sign_flag(str, options);
  s21_lf_width_flag(str, options);
  return str;
}

static char *s21_g_specifier(char *str, va_list *args, s_format *options) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (options->len) {
    case 'l':
      d_number = (double)va_arg(*args, double);
      s21_lg_to_str(str, d_number, options);
      break;
    case 'L':
      ld_number = va_arg(*args, long double);
      s21_lg_to_str(str, ld_number, options);
      break;
    default:
      d_number = va_arg(*args, double);
      f_number = d_number;
      s21_lg_to_str(str, f_number, options);
  }
  s21_sign_flag(str, options);
  s21_lf_width_flag(str, options);
  return str;
}

static char *s21_le_to_str(char *str, long double number, s_format *options) {
  if (options->precision < 0) options->precision = 6;
  long double right = 0.0, mantis;
  int pow = 0;

  mantis = modfl(fabsl(number), &right);
  if (fpclassify(number) > 3) {
    while (right >= 10) {
      pow++;
      modfl(right / 10, &right);
    }
    if (pow == 0 && right < 1) {
      while (truncl(mantis * powl(10, pow * -1)) < 1) {
        pow--;
      }
    }
  }

  if (fpclassify(number) > 2) {
    number = number / powl(10, pow);
    s21_sprintf(str, options->sharp == 1 ? "%#.*Lfe%+.2d" : "%.*Lfe%+.2d",
                options->precision, number, pow);
  } else {
    s21_sprintf(str, "%.*Lf", options->precision);
    options->zero = 0;
  }
  if (options->spec == 'E') {
    char *p = S21_NULL;
    p = s21_strchr(str, 'e');
    if (p) *p = 'E';
  }
  return str;
}

static char *s21_lg_to_str(char *str, long double number, s_format *options) {
  if (options->precision < 0) options->precision = 6;
  long double right = 0.0;
  int pow = 0;
  long double mantis = modfl(fabsl(number), &right);
  if (fpclassify(mantis) > 3 && fpclassify(right) == 3) {
    while (truncl(mantis * powl(10, pow * -1)) < 1) {
      pow--;
    }
  }
  mantis = modfl(fabsl(number), &right);
  if (fpclassify(number) > 3) {
    while (right >= 1 && pow >= 0) {
      pow++;
      modfl(right / 10, &right);
    }
    if (fpclassify(mantis) > 3) {
      for (int i = 0; i < options->precision - pow; i++) {
        mantis = modfl(right / 10, &right);
      }
    }
  }

  int flag;
  int precision;
  if (pow - 1 < -4 || pow - 1 > options->precision - 1) {
    flag = 1;
    precision = options->precision > 0 ? options->precision - 1 : 0;
  } else {
    flag = 0;
    if (pow < 0)
      precision = options->precision > 0 ? options->precision : 0;
    else
      precision = options->precision > 0 ? options->precision - pow : 0;
  }

  if (flag == 1) {
    if (options->spec == 'G')
      s21_sprintf(str, options->sharp == 1 ? "%#.*LE" : "%.*LE", precision,
                  number);
    else
      s21_sprintf(str, options->sharp == 1 ? "%#.*Le" : "%.*Le", precision,
                  number);
  } else {
    s21_sprintf(str, options->sharp == 1 ? "%#.*Lf" : "%.*Lf", precision,
                number);
  }

  char *p = S21_NULL;
  if (pow < 0 && flag == 1) {
    p = str;
    s21_size_t str_len = s21_strpbrk(str, options->spec == 'G' ? "E" : "e") - p;
    if (str_len > 2 && (int)str_len - 1 >= options->precision &&
        *(p + str_len - 1) == '0' && options->sharp == 0) {
      p = p + str_len - 1;
      while (*p == '0') {
        *(p--) = '\0';
      }
      p = str + str_len;
      s21_strcat(str, p);
    }
  }

  p = str;
  p = p + s21_strlen(str) - 1;

  while (*p == '0' && options->sharp != 1) {
    *p-- = '\0';
  }
  if (*p == '.' && options->sharp != 1) {
    *p = '\0';
  }

  return str;
}

static char *s21_lf_to_str(char *str, long double number, s_format *options) {
  if (options->precision < 0) options->precision = 6;
  s21_ld_to_str(str, number, options);
  return str;
}

static char *s21_s_specifier(char *str, va_list *args, s_format *options) {
  wchar_t *pw = S21_NULL;
  char *p = S21_NULL;

  switch (options->len) {
    case 'l':
      pw = va_arg(*args, wchar_t *);
      if (!pw) {
        if (options->precision < 6)
          s21_strncat(str, "(null)", options->precision);
        else
          s21_strcat(str, "(null)");
      } else {
        s21_wch_to_str(str, pw,
                       options->precision > -1 ? options->precision : 0);
      }
      break;
    default:
      p = va_arg(*args, char *);
      if (!p) {
        if (options->precision < 6)
          s21_strncat(str, "(null)", options->precision);
        else
          s21_strcat(str, "(null)");
      } else {
        if (options->precision > -1)
          s21_strncat(str, p, options->precision);
        else
          s21_strcat(str, p);
      }
  }
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_c_specifier(char *str, va_list *args, s_format *options) {
  wchar_t wchar;
  wchar_t wchar_s[10] = {0};
  switch (options->len) {
    case 'l':
      wchar = va_arg(*args, wchar_t);
      wchar_s[0] = wchar;
      s21_wch_to_str(str, wchar_s, 0);
      break;
    default:
      str[0] = va_arg(*args, int);
      str[1] = '\0';
  }
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_u_specifier(char *str, va_list *args, s_format *options) {
  unsigned short us_number;
  unsigned long ul_number;
  unsigned int u_number;

  switch (options->len) {
    case 'h':
      us_number = (unsigned short)va_arg(*args, unsigned int);
      s21_ll_to_str(str, us_number);
      break;
    case 'l':
      ul_number = (unsigned long)va_arg(*args, unsigned long);
      s21_ul_to_str(str, ul_number);
      break;
    default:
      u_number = (unsigned int)va_arg(*args, unsigned int);
      s21_ll_to_str(str, u_number);
  }

  s21_precision(str, options);
  s21_sign_flag(str, options);
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_d_specifier(char *str, va_list *args, s_format *options) {
  long int ld_number;
  short int sd_number;
  int number;

  switch (options->len) {
    case 'h':
      sd_number = (short int)va_arg(*args, int);
      s21_ll_to_str(str, sd_number);
      break;
    case 'l':
      ld_number = (long int)va_arg(*args, long int);
      s21_ll_to_str(str, ld_number);
      break;
    default:
      number = va_arg(*args, int);
      s21_ll_to_str(str, number);
  }
  s21_precision(str, options);
  s21_sign_flag(str, options);
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_o_specifier(char *str, va_list *args, s_format *options) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (options->len) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*args, unsigned int);
      s21_ol_to_str(str, sd_number, options->sharp);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*args, unsigned long int);
      s21_ol_to_str(str, ld_number, options->sharp);
      break;
    default:
      number = va_arg(*args, unsigned int);
      s21_ol_to_str(str, number, options->sharp);
  }
  s21_precision(str, options);
  s21_sign_flag(str, options);
  s21_ll_width_flag(str, options);
  return str;
}

static char *s21_x_specifier(char *str, va_list *args, s_format *options) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (options->len) {
    case 'h':
      sd_number = (short unsigned int)va_arg(*args, unsigned int);
      s21_hl_to_str(str, sd_number, options);
      break;
    case 'l':
      ld_number = (long unsigned int)va_arg(*args, unsigned long int);
      s21_hl_to_str(str, ld_number, options);
      break;
    default:
      number = (unsigned int)va_arg(*args, unsigned int);
      s21_hl_to_str(str, number, options);
  }
  s21_precision(str, options);
  s21_sign_flag(str, options);
  s21_ll_width_flag(str, options);

  return str;
}

static char *s21_lf_width_flag(char *str, s_format *options) {
  int str_len = (int)s21_strlen(str);
  char *p = S21_NULL, *p2 = S21_NULL;
  p2 = str;
  if (options->width > (int)str_len) {
    char *num_str = calloc(1000 + options->width + 2, sizeof(char));
    if (num_str) {
      p = num_str;
      if (!is_digit(*p2) && options->zero) {
        *(p++) = *(p2++);
      }
      for (int i = 0; i < options->width; i++) {
        if (options->minus == 1) {
          if (i < str_len) {
            *(p++) = *(p2++);
          } else {
            if (options->zero == 1)
              *(p++) = '0';
            else
              *(p++) = ' ';
          }
        } else {
          if (i < options->width - str_len) {
            if (options->zero == 1)
              *(p++) = '0';
            else
              *(p++) = ' ';
          } else {
            *(p++) = *(p2++);
          }
        }
      }
      num_str[options->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

static char *s21_ll_width_flag(char *str, s_format *options) {
  int str_len = (int)s21_strlen(str);
  if (options->width > (int)str_len) {
    char *num_str = calloc(1000 + options->width + 2, sizeof(char));
    if (num_str) {
      for (int i = 0; i < options->width; i++) {
        if (options->minus == 1) {
          if (i < str_len) {
            num_str[i] = str[i];
          } else {
            num_str[i] = ' ';
          }
        } else {
          if (i < options->width - str_len) {
            num_str[i] = ' ';
          } else {
            num_str[i] = str[i - (options->width - str_len)];
          }
        }
      }
      num_str[options->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

static char *s21_wch_to_str(char *str, wchar_t *wstr, s21_size_t len) {
  s21_size_t str_len = s21_strlen(str);
  int cnt = len;
  char *p = str + str_len;

  while (*wstr != '\0' && (cnt-- > 0 || len == 0)) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
  return str;
}

static char *s21_sign_flag(char *str, s_format *options) {
  if (is_digit(*str) || *str == 'i') {
    char num_str[2] = "";
    char *p = S21_NULL;
    p = num_str;
    if (options->plus)
      *(p++) = '+';
    else if (options->space)
      *(p++) = ' ';
    *p = '\0';
    s21_reverse_str(str);
    s21_strcat(str, num_str);
    s21_reverse_str(str);
  }
  return str;
}

static char *s21_precision(char *str, s_format *options) {
  char *num_str = calloc(1000 + options->width + 2, sizeof(char));
  if (num_str) {
    s21_size_t str_len = s21_strlen(str);
    int shift;
    char *p = S21_NULL;
    char *s = S21_NULL;
    p = num_str;
    s = str;

    int sign = *s == '-' ? -1 : 0;
    if (options->zero == 1)
      options->precision = (options->precision > options->width)
                               ? options->precision
                               : options->width;

    options->precision = options->precision > (int)str_len + sign
                             ? options->precision
                             : (int)str_len + sign;
    shift = options->spec == 'x' && options->sharp == 1 ? 32 : 0;

    s21_reverse_str(str);
    for (int i = 0; i < options->precision; i++) {
      if (i < (int)str_len + sign)
        *(p++) = *(s++);
      else
        *(p++) = '0';
    }

    if (options->sharp == 1 && options->spec == (char)('X' + shift)) {
      *(p++) = (char)('X' + shift);
      *(p++) = '0';
    }

    if (sign < 0) *(p++) = '-';
    *p = '\0';
    s21_reverse_str(num_str);
    s21_strcpy(str, num_str);
    free(num_str);
  }
  return str;
}

static char *s21_ll_to_str(char *str, long long number) {
  char *p = S21_NULL;
  int flag = 1, sign;

  sign = number < 0 ? -1 : 1;
  number *= sign;
  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (sign < 0) {
    *(p++) = '-';
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

static char *s21_ul_to_str(char *str, unsigned long long number) {
  char *p = S21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

static char *s21_ol_to_str(char *str, unsigned long long number, int prefix) {
  char *p = S21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (prefix == 1) *(p++) = '0';
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

static char *s21_hl_to_str(char *str, unsigned long long number,
                           s_format *options) {
  char *p = S21_NULL;
  int flag = 1, shift;

  p = str;

  shift = options->spec == 'x' ? 32 : 0;

  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(p++) = (char)(digit + '0');
    else
      *(p++) = (char)(digit + 'A' + shift - 10);
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

static char *s21_str_to_int(const char *format, int *number, va_list *args) {
  *number = 0;
  while (is_digit(*format)) {
    *number = *format - '0' + *number * 10;
    format++;
  }
  if (*format == '*') {
    *number = va_arg(*args, int);
    format++;
  }
  return (char *)format;
}

static char *s21_reverse_str(char *str) {
  s21_size_t str_len = s21_strlen(str);
  char ch;
  for (s21_size_t i = 0; i < str_len / 2; i++) {
    ch = str[i];
    str[i] = str[str_len - 1 - i];
    str[str_len - 1 - i] = ch;
  }
  return str;
}

static long double s21_round(long double x, int precision) {
  long double right = 0.0;
  long double x1 = modfl(fabsl(x), &right);
  int mul = 0;
  int sign = signbit(x) == 0 ? 1 : -1;
  for (int i = 0; i < precision; i++) mul--;

  if (roundl(x1 / powl(10, mul)) > truncl(x1 / powl(10, mul))) {
    x = x + (5 * powl(10, mul - 1)) * sign;
  }
  if (precision <= 6 && x1 > 0) {
    x = x / powl(10, mul);
    x = truncl(x) * powl(10, mul);
  }
  return x;
}

static char *s21_ld_to_str(char *str, long double number, s_format *options) {
  char num1_str[1000] = "", *p1 = S21_NULL;
  p1 = num1_str;
  char num2_str[1000] = "", *p2 = S21_NULL;
  p2 = num2_str;
  long double mantis, right = 0.0L, pow = 1.0L, pow_t = 1.0L;
  int sign;
  sign = signbit(number) == 0 ? 1 : -1;

  if (fpclassify(number) < 4) {
    s21_d_class_to_str(num1_str, number, options->precision);
    if (sign < 0 && fpclassify(number) != 1) s21_strcat(str, "-");
    s21_strcat(str, num1_str);
    options->zero = 0;
  } else {
    number = s21_round(number, options->precision);
    mantis = modfl(fabsl(number), &right);

    while (truncl(right / pow) > 0) {
      int digit;
      digit = (int)truncl(fmodl(truncl(right), pow * (long double)10L) / (pow));
      *(p1++) = (char)(digit + '0');
      pow *= 10L;
    }

    if (sign < 0) *(p1++) = '-';
    *p1 = '\0';

    for (int i = 0; i < options->precision; i++) pow_t *= 10;

    mantis = roundl(mantis * pow_t);
    pow = 1.0L;
    while (pow < pow_t) {
      int digit;
      digit =
          (int)truncl(fmodl(truncl(mantis), pow * (long double)10L) / (pow));
      *(p2++) = (char)(digit + '0');
      pow *= 10L;
    }
    *p2 = '\0';
    s21_reverse_str(num1_str);
    if (s21_strlen(num1_str) == 0) s21_strcat(str, "0");
    s21_strcat(str, num1_str);
    if (options->precision > 0 || options->sharp == 1) s21_strcat(str, ".");
    if (options->precision > 0) {
      s21_reverse_str(num2_str);
      s21_strcat(str, num2_str);
    }
  }
  return str;
}

static char *s21_d_class_to_str(char *str, long double x, int precision) {
  switch (fpclassify(x)) {
    case FP_NAN:
      s21_strcat(str, "nan");
      break;
    case FP_INFINITE:
      s21_strcat(str, "inf");
      break;
    case FP_ZERO:
      s21_strcat(str, "0");
      if (precision > 0) {
        s21_strcat(str, ".");
        while (precision--) s21_strcat(str, "0");
      }
      break;
  }
  return str;
}
