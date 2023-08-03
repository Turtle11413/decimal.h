#include "../s21_decimal.h"
#include "../utility.h"

int s21_truncate_long(s21_long_decimal src, s21_long_decimal *dst) {
  int exp = get_exp_long(src);
  int sign = get_sign_long(src);
  set_sign_long(&src, 0);
  s21_long_decimal temp = {{0}};

  for (int i = 0; i < exp; ++i) {
    s21_div_ten_long(src, &temp);
    src = temp;
    for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) temp.bits[i] = 0;
  }
  for (int i = 0; i < BITS_SIZE_LONG; ++i) dst->bits[i] = src.bits[i];
  set_exp_long(dst, 0);
  set_sign_long(dst, sign);
  return 0;
}

int s21_truncate(s21_decimal src, s21_decimal *dst) {
  s21_long_decimal lsrc = {{0}}, ldst = {{0}};
  s21_from_decimal_to_long_decimal(src, &lsrc);
  s21_truncate_long(lsrc, &ldst);
  s21_from_long_decimal_to_decimal(ldst, dst);
  return 0;
}
