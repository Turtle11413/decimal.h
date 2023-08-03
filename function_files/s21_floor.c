#include "../s21_decimal.h"
#include "../utility.h"

int s21_floor_long(s21_long_decimal src, s21_long_decimal *dst) {
  int sign = get_sign_long(src);
  int exp = get_exp_long(src);
  s21_truncate_long(src, dst);
  if (sign && exp) {
    s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
    s21_sub_long(*dst, one, dst);
  }
  return 0;
}

int s21_floor(s21_decimal src, s21_decimal *dst) {
  s21_long_decimal lsrc = {{0}}, ldst = {{0}};
  s21_from_decimal_to_long_decimal(src, &lsrc);
  s21_floor_long(lsrc, &ldst);
  s21_from_long_decimal_to_decimal(ldst, dst);
  return 0;
}
