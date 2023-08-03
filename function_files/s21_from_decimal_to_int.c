#include "../s21_decimal.h"
#include "../utility.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_value = 0;

  int sign = get_sign(src);

  s21_decimal max_int = {{0}}, min_int = {{0}};
  s21_from_int_to_decimal(MAXINT, &max_int);
  s21_from_int_to_decimal(MININT, &min_int);

  if (s21_is_greater_or_equal(src, min_int) &&
      s21_is_less_or_equal(src, max_int)) {
    s21_decimal result = {{0}};
    s21_truncate(src, &result);
    *dst = result.bits[0];
  } else {
    return_value = 1;
  }

  if (sign) {
    (*dst) *= -1;
  }

  return return_value;
}
