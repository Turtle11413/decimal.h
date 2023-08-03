#include "../s21_decimal.h"
#include "../utility.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  for (int i = 0; i <= 3; i++) result->bits[i] = 0;
  int return_value = 0;

  s21_long_decimal v1, v2, res = {{0}};
  s21_from_decimal_to_long_decimal(value_1, &v1);
  s21_from_decimal_to_long_decimal(value_2, &v2);
  s21_normalize_long(&v1, &v2);

  s21_add_long(v1, v2, &res);
  return_value = s21_from_long_decimal_to_decimal(res, result);
  set_exp(result, get_exp_long(v1));

  return return_value;
}

int s21_add_long(s21_long_decimal value_1, s21_long_decimal value_2,
                 s21_long_decimal *result) {
  for (int i = 0; i < BITS_SIZE_LONG - 1; i++) result->bits[i] = 0;
  int return_value = 0;
  unsigned int intermediate_value = 0;

  if (get_sign_long(value_1) && !get_sign_long(value_2)) {
    set_sign_long(&value_1, 0);
    return_value = s21_sub_long(value_2, value_1, result);
  } else if (get_sign_long(value_2) && !get_sign_long(value_1)) {
    set_sign_long(&value_2, 0);
    return_value = s21_sub_long(value_1, value_2, result);
  } else {
    if (get_sign_long(value_2) && get_sign_long(value_1)) {
      set_sign_long(&value_1, 0);
      set_sign_long(&value_2, 0);
      set_sign_long(result, 1);
    }

    for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
      unsigned int max_value = 0, min_value = 0;
      max_value = (value_1.bits[i] > value_2.bits[i]) ? value_1.bits[i]
                                                      : value_2.bits[i];
      min_value = (value_1.bits[i] < value_2.bits[i]) ? value_1.bits[i]
                                                      : value_2.bits[i];

      if (intermediate_value == 1) {
        result->bits[i] += intermediate_value--;
      }

      if (max_value > UINT_MAX - min_value - result->bits[i]) {
        intermediate_value += 1;
        result->bits[i] += min_value - (UINT_MAX - max_value) - 1;
      } else {
        result->bits[i] += value_1.bits[i] + value_2.bits[i];
      }
    }

    if (intermediate_value != 0) {
      return_value = (!get_sign_long(*result)) ? 1 : 2;
    }
  }
  return return_value;
}
