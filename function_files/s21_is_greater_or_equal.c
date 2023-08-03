#include "../s21_decimal.h"
#include "../utility.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!s21_is_less(value_1, value_2)) || (s21_is_equal(value_1, value_2));
}

int s21_is_greater_or_equal_long(s21_long_decimal value_1,
                                 s21_long_decimal value_2) {
  return !s21_is_less_long(value_1, value_2) ||
         s21_is_equal_long(value_1, value_2);
}

int s21_is_greater_or_equal_long_int(s21_long_decimal value_1,
                                     s21_long_decimal value_2) {
  return !s21_is_less_long_int(value_1, value_2) ||
         s21_is_equal_long_int(value_1, value_2);
}
