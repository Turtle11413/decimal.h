#include "../s21_decimal.h"
#include "../utility.h"

int s21_round_n_long(s21_long_decimal src, s21_long_decimal *dst, int n) {
  int e = get_exp_long(src);
  if (e != 0) {
    int sign = get_sign_long(src);
    set_sign_long(&src, 0);
    unsigned int d;
    s21_long_decimal d_dec = {{0}};
    s21_long_decimal a1 = src;
    for (int i = 0; i < BITS_SIZE_LONG; ++i) dst->bits[i] = 0;

    for (int i = 0; i < e - n - 1; i++) {
      s21_long_decimal temp = {{0}};
      s21_div_ten_long(a1, &temp);
      a1 = temp;
    }
    s21_long_decimal temp = {{0}}, a2 = a1;
    s21_div_ten_long(a2, &temp);
    mul_int_ten_long(temp, &a2);
    set_exp_long(&a2, get_exp_long(a1));
    s21_sub_long(a1, a2, &d_dec);
    d = d_dec.bits[0];

    s21_div_ten_long(a2, dst);
    if (d >= 5) {
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
      a2.bits[BITS_SIZE_LONG - 1] = 0;
      s21_add_long(*dst, one, dst);
    }
    set_exp_long(dst, n);
    set_sign_long(dst, sign);
    remove_trailing_zeroes_long(dst);
  } else {
    for (int i = 0; i < BITS_SIZE_LONG; ++i) dst->bits[i] = src.bits[i];
  }

  return 0;
}

int s21_bank_round_n_long(s21_long_decimal src, s21_long_decimal *dst, int n) {
  int e = get_exp_long(src);
  if (e != 0) {
    int sign = get_sign_long(src);
    set_sign_long(&src, 0);
    unsigned int d;
    s21_long_decimal d_dec = {{0}};
    s21_long_decimal a1 = src;
    for (int i = 0; i < BITS_SIZE_LONG; ++i) dst->bits[i] = 0;

    for (int i = 0; i < e - n - 1; i++) {
      s21_long_decimal temp = {{0}};
      s21_div_ten_long(a1, &temp);
      a1 = temp;
    }
    s21_long_decimal temp = {{0}}, a2 = a1;
    s21_div_ten_long(a2, &temp);
    mul_int_ten_long(temp, &a2);
    set_exp_long(&a2, get_exp_long(a1));
    s21_sub_long(a1, a2, &d_dec);
    d = d_dec.bits[0];

    s21_div_ten_long(a2, dst);
    if (d == 5) {
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
      int ldz = s21_mod_ten_long(*dst);
      if (ldz % 2 == 1) {
        s21_add_long(*dst, one, dst);
      }
    } else if (d > 5) {
      s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
      a2.bits[BITS_SIZE_LONG - 1] = 0;
      s21_add_long(*dst, one, dst);
    }
    set_exp_long(dst, n);
    set_sign_long(dst, sign);
    remove_trailing_zeroes_long(dst);
  } else {
    for (int i = 0; i < BITS_SIZE_LONG; ++i) dst->bits[i] = src.bits[i];
  }

  return 0;
}

int s21_round_n(s21_decimal src, s21_decimal *dst, int n) {
  s21_long_decimal lsrc, ldst;
  s21_from_decimal_to_long_decimal(src, &lsrc);
  s21_from_decimal_to_long_decimal(*dst, &ldst);
  s21_round_n_long(lsrc, &ldst, n);
  for (int i = 0; i < BITS_SIZE - 1; ++i) dst->bits[i] = ldst.bits[i];
  dst->bits[BITS_SIZE - 1] = ldst.bits[BITS_SIZE_LONG - 1];

  return 0;
}

int s21_round(s21_decimal src, s21_decimal *dst) {
  return s21_round_n(src, dst, 0);
}
