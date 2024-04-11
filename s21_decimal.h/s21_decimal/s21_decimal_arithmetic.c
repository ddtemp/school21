#include "../s21_decimal.h"
#include "s21_decimal_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign = 0;
  unsigned buf_1[6] = {0, 0, 0, 0, 0, 0};
  unsigned buf_2[6] = {0, 0, 0, 0, 0, 0};
  unsigned buf_result[6] = {0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 3; i++) {
    buf_1[i] = value_1.bits[i];
    buf_2[i] = value_2.bits[i];
  }

  int scale = s21_get_scale(value_1) >= s21_get_scale(value_2)
                  ? s21_get_scale(value_1)
                  : s21_get_scale(value_2);

  s21_to_scale(value_1, scale, buf_1, 6);
  s21_to_scale(value_2, scale, buf_2, 6);

  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    sign = s21_get_sign(value_1);
  } else {
    if (s21_data_gt(buf_1, buf_2, 6) || s21_data_eq(buf_1, buf_2, 6)) {
      s21_negate_data(buf_2, 6);
      sign = s21_get_sign(value_1);
    } else {
      s21_negate_data(buf_1, 6);
      sign = s21_get_sign(value_2);
    }
  }

  s21_data_add(buf_1, buf_2, buf_result, 6);
  int last_digit = 0;
  while ((scale && (buf_result[5] || buf_result[4] || buf_result[3])) ||
         scale > 28) {
    last_digit = s21_mod10mem(buf_result, 6);
    s21_div10mem(buf_result, buf_result, 6);
    scale--;
  }

  if (last_digit >= 5) {
    unsigned carry[6] = {1, 0, 0, 0, 0, 0};
    s21_data_add(buf_result, carry, buf_result, 6);
  }

  if (!(buf_result[5] || buf_result[4] || buf_result[3])) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = buf_result[i];
    }
    result->bits[3] = sign << 31;
    s21_set_scale(result, scale);
  } else {
    err = 1 + sign;
  }
  return err;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_negate(value_2, &value_2);
  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_null(value_1) || s21_is_null(value_2)) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    return 0;
  }

  int sign = (s21_get_sign(value_1) == s21_get_sign(value_2)) ? 0 : 1;
  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

  unsigned buf_1[6] = {
      value_1.bits[0], value_1.bits[1], value_1.bits[2], 0, 0, 0};
  unsigned buf_2[6] = {
      value_2.bits[0], value_2.bits[1], value_2.bits[2], 0, 0, 0};
  unsigned buf_result[6] = {0, 0, 0, 0, 0, 0};

  while (buf_1[0] || buf_1[1] || buf_1[2]) {
    if (buf_1[0] & 1) {
      s21_data_add(buf_result, buf_2, buf_result, 6);
    }
    s21_div2mem(buf_1, 6);
    s21_data_add(buf_2, buf_2, buf_2, 6);
  }

  int last_digit = 0;
  while ((scale && (buf_result[5] || buf_result[4] || buf_result[3])) ||
         scale > 28) {
    last_digit = s21_mod10mem(buf_result, 6);
    s21_div10mem(buf_result, buf_result, 6);
    scale--;
  }

  if (last_digit >= 5) {
    unsigned carry[6] = {1, 0, 0, 0, 0, 0};
    s21_data_add(buf_result, carry, buf_result, 6);
  }

  if (buf_result[3] || buf_result[4] || buf_result[5]) {
    return 1;
  }

  for (int i = 0; i < 3; i++) {
    result->bits[i] = buf_result[i];
  }
  result->bits[3] = sign << 31;
  s21_set_scale(result, scale);

  return 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int scale = s21_get_scale(value_1) >= s21_get_scale(value_2)
                  ? s21_get_scale(value_1)
                  : s21_get_scale(value_2);

  int sign = s21_get_sign(value_1) != s21_get_sign(value_2);

  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    err = 3;
  } else {
    unsigned buf_1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned buf_2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned buf_result[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 3; i++) {
      buf_1[i] = value_1.bits[i];
      buf_2[i] = value_2.bits[i];
    }

    s21_to_scale(value_1, scale + 29, buf_1, 9);
    s21_to_scale(value_2, scale + 29, buf_2, 9);
    scale = -1;
    while (s21_data_gt(buf_1, buf_2, 9)) {
      s21_mul_pow10mem(buf_2, 1, 9);
      scale--;
    }
    while ((buf_1[0] || buf_1[1] || buf_1[2] || buf_1[3] || buf_1[4] ||
            buf_1[5] || buf_1[6] || buf_1[7] || buf_1[8]) &&
           (buf_2[0] || buf_2[1] || buf_2[2] || buf_2[3] || buf_2[4] ||
            buf_2[5] || buf_2[6] || buf_2[7] || buf_2[8])) {
      s21_mul10mem(buf_result, 9);

      while (s21_data_gt(buf_1, buf_2, 9) || s21_data_eq(buf_1, buf_2, 9)) {
        s21_data_sub(buf_1, buf_2, buf_1, 9);
        buf_result[0] += 1;
      }

      s21_div10mem(buf_2, buf_2, 9);
      scale++;
    }
    int last_digit = 0;
    while ((buf_result[8] || buf_result[7] || buf_result[6] || buf_result[5] ||
            buf_result[4] || buf_result[3]) ||
           scale > 28) {
      last_digit = s21_mod10mem(buf_result, 9);
      s21_div10mem(buf_result, buf_result, 9);
      scale--;
    }
    if (last_digit >= 5) {
      unsigned carry[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
      s21_data_add(buf_result, carry, buf_result, 9);
    }
    if (!(buf_result[8] || buf_result[7] || buf_result[6] || buf_result[5] ||
          buf_result[4] || buf_result[3])) {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = buf_result[i];
      }
      result->bits[3] = (sign << 31);
      s21_set_scale(result, scale);
    } else {
      err = 1 + sign;
    }
  }
  return err;
}
