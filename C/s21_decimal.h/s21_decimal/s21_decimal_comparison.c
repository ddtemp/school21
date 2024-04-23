#include "../s21_decimal.h"
#include "s21_decimal_helpers.h"

static int multiply_mantissa_by_value(uint32_t *mantissa, int value) {
  uint64_t buffer = 0ULL;

  for (int i = 0; i < 3; i++) {
    buffer += (uint64_t)(mantissa[i]) * (uint64_t)value;
    mantissa[i] = (uint32_t)(buffer & 0xFFFFFFFFULL);
    buffer = (buffer >> 32);
  }

  return buffer ? 1 : 0;
}

static int to_new_scale(s21_decimal *value, int scale) {
  int too_large_value_flag = 0;

  for (int i = s21_get_scale(*value); i < scale && !too_large_value_flag; i++) {
    too_large_value_flag = multiply_mantissa_by_value(value->bits, 10);
  }

  return too_large_value_flag;
}

static int to_common_exp(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = s21_get_scale(*value_1);
  int exp_2 = s21_get_scale(*value_2);
  int scale = ((exp_1 > exp_2) ? exp_1 : exp_2);

  int flag_1 = to_new_scale(value_1, scale);
  int flag_2 = to_new_scale(value_2, scale);

  int ret = k_equal;

  if (flag_1 > flag_2) {
    ret = k_greater;
  } else if (flag_1 < flag_2) {
    ret = k_less;
  }

  return ret;
}

static int bitwise_comparison(s21_decimal value_1, s21_decimal value_2) {
  int ret = k_equal;

  for (int i = 2; i >= 0 && ret == k_equal; i--) {
    if (value_1.bits[i] > value_2.bits[i]) {
      ret = k_greater;
    } else if (value_1.bits[i] < value_2.bits[i]) {
      ret = k_less;
    }
  }

  return ret;
}

static int compare_mantises(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal buffer_1 = {{0, 0, 0, 0}};
  s21_decimal buffer_2 = {{0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    buffer_1.bits[i] = value_1.bits[i];
    buffer_2.bits[i] = value_2.bits[i];
  }

  int ret = to_common_exp(&buffer_1, &buffer_2);

  if (ret == k_equal) ret = bitwise_comparison(buffer_1, buffer_2);

  return ret;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int ret = k_false;

  int is_not_zero = value_1.bits[0] | value_1.bits[1] | value_1.bits[2] |
                    value_2.bits[0] | value_2.bits[1] | value_2.bits[2];

  int is_same_sign = (s21_get_sign(value_1) == s21_get_sign(value_2));

  int is_equal_mantises = compare_mantises(value_1, value_2);

  if (!is_not_zero) {
    ret = k_true;
  } else if (!is_same_sign) {
    ret = k_false;
  } else if (!is_equal_mantises) {
    ret = k_true;
  } else {
    ret = k_false;
  }

  return ret;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_equal(value_1, value_2));
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int ret = k_false;

  if (s21_is_equal(value_1, value_2)) {
    ret = k_false;
  } else if (s21_get_sign(value_1) < s21_get_sign(value_2)) {
    ret = k_true;
  } else if (s21_get_sign(value_1) > s21_get_sign(value_2)) {
    ret = k_false;
  } else {
    int negative_sign_flag = s21_get_sign(value_1);
    switch (compare_mantises(value_1, value_2)) {
      case k_equal:
        ret = k_false;
        break;

      case k_greater:
        ret = (negative_sign_flag ? k_false : k_true);
        break;

      case k_less:
        ret = (negative_sign_flag ? k_true : k_false);
        break;
    }
  }

  return ret;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_greater_or_equal(value_1, value_2));
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
}
