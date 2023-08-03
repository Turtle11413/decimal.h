#include "../s21_decimal.h"
#include "../utility.h"

int s21_div_ten_long(s21_long_decimal value_1, s21_long_decimal* result) {
  int result_value = 0;

  s21_long_decimal zero = {{0}};
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal divider = ten;
  int sign = get_sign_long(value_1);
  set_sign_long(&value_1, 0);

  if (!s21_is_equal_long_int(divider, zero)) {
    if (s21_is_greater_or_equal_long_int(value_1, divider)) {
      int i = 0;
      while (s21_is_less_or_equal_long_int(divider, value_1)) {
        i++;
        move_long_decimal_left(&divider);
      }

      s21_long_decimal add_value = {{1, 0, 0, 0, 0, 0, 0}};
      for (int j = 0; j < i - 1; ++j) move_long_decimal_left(&add_value);
      s21_add_long(*result, add_value, result);

      s21_mul_int_long(ten, add_value, &add_value);

      s21_sub_long_int(value_1, add_value, &value_1);

      s21_div_ten_long(value_1, result);
    }
  } else {
    result_value = 3;
  }
  set_sign_long(&value_1, sign);

  return result_value;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int result_value = 0;

  s21_decimal divider = value_2;
  set_sign(&divider, 0);
  s21_decimal zero = {{0}};

  for (int i = 0; i < BITS_SIZE; ++i) {
    result->bits[i] = 0;
  }

  int sign_value_1 = get_sign(value_1);
  set_sign(&value_1, 0);
  int sign_value_2 = get_sign(value_2);
  set_sign(&value_2, 0);

  int result_exp = 0;

  if (!s21_is_equal(divider, zero)) {
    s21_long_decimal long_value_1 = {{0}}, long_value_2 = {{0}},
                     long_result = {{0}};
    s21_from_decimal_to_long_decimal(value_1, &long_value_1);
    s21_from_decimal_to_long_decimal(value_2, &long_value_2);
    s21_normalize_long(&long_value_1, &long_value_2);

    set_exp_long(&long_value_1, 0);
    set_exp_long(&long_value_2, 0);

    s21_div_long(long_value_1, long_value_2, &long_result, &result_exp);

    set_exp_long(&long_result, result_exp);

    result_value = s21_from_long_decimal_to_decimal(long_result, result);
    if ((result->bits[0] == 0) && (result->bits[1] == 0) &&
        (result->bits[2] == 0) && (result->bits[3] != 0)) {
      result_value = 2;
    }

  } else {
    result_value = 3;
  }

  if (!result_value) set_sign(result, (sign_value_1 ^ sign_value_2));

  return result_value;
}

void s21_div_long(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal* result, int* result_exp) {
  s21_long_decimal zero = {{0}};
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal divider = value_2;

  if (s21_is_greater_or_equal_long(value_1, divider)) {
    int i = 0;
    while (s21_is_less_or_equal_long(divider, value_1)) {
      i++;
      move_long_decimal_left(&divider);
    }
    s21_long_decimal add_value = {{1, 0, 0, 0, 0, 0, 0}};
    for (int j = 0; j < i - 1; ++j) move_long_decimal_left(&add_value);
    s21_add_long(*result, add_value, result);
    s21_mul_int_long(value_2, add_value, &add_value);
    s21_sub_long(value_1, add_value, &value_1);
    s21_div_long(value_1, value_2, result, result_exp);
  } else if (!s21_is_equal_long(value_1, zero) && (*result_exp < 30)) {
    s21_mul_int_long(value_1, ten, &value_1);
    s21_mul_int_long(*result, ten, result);
    (*result_exp)++;
    s21_div_long(value_1, value_2, result, result_exp);
  }
}
