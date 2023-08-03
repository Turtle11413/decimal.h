#include "../s21_decimal.h"
#include "../utility.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal v1l, v2l;
  s21_from_decimal_to_long_decimal(value_1, &v1l);
  s21_from_decimal_to_long_decimal(value_2, &v2l);
  return s21_is_equal_long(v1l, v2l);
}

int s21_is_equal_long(s21_long_decimal value_1, s21_long_decimal value_2) {
  int result = 1;
  if (!(s21_is_null_long(value_1) && s21_is_null_long(value_2))) {
    s21_normalize_long(&value_1, &value_2);
    value_1.bits[BITS_SIZE_LONG - 1] &= VAL_MASK;
    value_2.bits[BITS_SIZE_LONG - 1] &= VAL_MASK;
    for (int i = 0; i < BITS_SIZE_LONG; ++i) {
      if (value_1.bits[i] != value_2.bits[i]) {
        result = 0;
        break;
      }
    }
  }
  return result;
}

int s21_is_equal_long_int(s21_long_decimal value_1, s21_long_decimal value_2) {
  int result = 1;
  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    if (value_1.bits[i] != value_2.bits[i]) {
      result = 0;
      break;
    }
  }
  return result;
}
