#include "../s21_decimal.h"
#include "../utility.h"

void swap_long(s21_long_decimal *v1, s21_long_decimal *v2) {
  s21_long_decimal tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i <= 3; i++) result->bits[i] = 0;
  int return_value = 0;

  s21_long_decimal v1, v2, res = {{0}};
  s21_from_decimal_to_long_decimal(value_1, &v1);
  s21_from_decimal_to_long_decimal(value_2, &v2);
  s21_normalize_long(&v1, &v2);

  s21_sub_long(v1, v2, &res);
  return_value = s21_from_long_decimal_to_decimal(res, result);
  set_exp(result, get_exp_long(v1));

  return return_value;
}

int s21_sub_long(s21_long_decimal value_1, s21_long_decimal value_2,
                 s21_long_decimal *result) {
  int return_value = 0;
  unsigned int intermediate_flag = 0;

  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    result->bits[i] = 0;
  }

  if (!get_sign_long(value_1) && get_sign_long(value_2)) {
    set_sign_long(&value_2, 0);
    return_value = s21_add_long(value_1, value_2, result);
  } else if (!get_sign_long(value_2) && get_sign_long(value_1)) {
    set_sign_long(&value_1, 0);
    return_value = s21_add_long(value_1, value_2, result);
    set_sign_long(result, 1);
    if (return_value) return_value = 2;
  } else if (get_sign_long(value_1) && get_sign_long(value_2)) {
    set_sign_long(&value_1, 0);
    set_sign_long(&value_2, 0);
    return_value = s21_sub_long(value_2, value_1, result);
  } else {
    if (s21_is_less_long(value_1, value_2)) {
      swap_long(&value_1, &value_2);
      set_sign_long(result, 1);
    }

    for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
      if (intermediate_flag) {
        if (value_1.bits[i] >= value_2.bits[i] + 1) {
          value_1.bits[i]--;
          intermediate_flag = 0;
        } else {
          value_1.bits[i] = UINT_MAX;
        }
      }
      if (value_1.bits[i] < value_2.bits[i]) {
        intermediate_flag = 1;
        result->bits[i] += UINT_MAX - value_2.bits[i] + value_1.bits[i] + 1;
      } else {
        result->bits[i] += value_1.bits[i] - value_2.bits[i];
      }
    }
    if (intermediate_flag != 0) {
      return_value = 2;
    }
  }

  return return_value;
}

int s21_sub_long_int(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result) {
  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    result->bits[i] = 0;
  }

  int return_value = 0;
  unsigned int intermediate_flag = 0;

  for (int i = 0; i < BITS_SIZE_LONG - 1; i++) result->bits[i] = 0;

  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    if (intermediate_flag) {
      if (value_1.bits[i] >= value_2.bits[i] + 1) {
        value_1.bits[i]--;
        intermediate_flag = 0;
      } else {
        value_1.bits[i] = UINT_MAX;
      }
    }
    if (value_1.bits[i] < value_2.bits[i]) {
      intermediate_flag = 1;
      result->bits[i] += UINT_MAX - value_2.bits[i] + value_1.bits[i] + 1;
    } else {
      result->bits[i] += value_1.bits[i] - value_2.bits[i];
    }
  }
  if (intermediate_flag != 0) {
    return_value = 2;
  }
  return return_value;
}
