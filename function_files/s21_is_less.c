#include "../s21_decimal.h"
#include "../utility.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal v1l, v2l;
  s21_from_decimal_to_long_decimal(value_1, &v1l);
  s21_from_decimal_to_long_decimal(value_2, &v2l);
  return s21_is_less_long(v1l, v2l);
}

int s21_is_less_long(s21_long_decimal value_1, s21_long_decimal value_2) {
  int result_value = 0;
  int sign1 = get_sign_long(value_1);
  int sign2 = get_sign_long(value_2);
  s21_long_decimal values[2] = {value_1, value_2};
  if (s21_is_null_long(value_1) && s21_is_null_long(value_2)) {
    result_value = 0;
  } else if (sign1 ^ sign2) {
    result_value = sign1 == 1 ? 1 : 0;
  } else {
    s21_normalize_long(&values[0], &values[1]);
    for (int i = BITS_SIZE_LONG - 2; i >= 0; --i) {
      if (values[sign1].bits[i] == values[!sign1].bits[i])
        ;
      else if (values[sign1].bits[i] < values[!sign1].bits[i]) {
        result_value = 1;
        i = -1;
      } else {
        result_value = 0;
        i = -1;
      }
    }
  }

  return result_value;
}

int s21_is_less_long_int(s21_long_decimal value_1, s21_long_decimal value_2) {
  int result_value = 0;
  int sign1 = get_sign_long(value_1);
  int sign2 = get_sign_long(value_2);
  s21_long_decimal values[2] = {value_1, value_2};
  if (sign1 ^ sign2) {
    result_value = sign1 == 1 ? 1 : 0;
  } else {
    /* s21_normalize_long(&values[0], &values[1]); */
    for (int i = BITS_SIZE_LONG - 2; i >= 0; --i) {
      if (values[sign1].bits[i] == values[!sign1].bits[i])
        ;
      else if (values[sign1].bits[i] < values[!sign1].bits[i]) {
        result_value = 1;
        i = -1;
      } else {
        result_value = 0;
        i = -1;
      }
    }
  }

  return result_value;
}
