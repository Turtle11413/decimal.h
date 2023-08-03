#include "../utility.h"

#include "../s21_decimal.h"

int get_exp(s21_decimal value) { return ((value.bits[3] & EXP_MASK) >> 16); }

int get_sign(s21_decimal value) { return ((value.bits[3] & SIGN_MASK) >> 31); }

void set_exp(s21_decimal *value, int exp) {
  value->bits[3] &= ~EXP_MASK;
  value->bits[3] += exp << 16;
}

void set_sign(s21_decimal *value, int sign) {
  value->bits[3] &= ~SIGN_MASK;
  value->bits[3] += sign << 31;
}

void move_decimal_right(s21_decimal *value) {
  int preserve_bit, preserve_bit_prev = 0;
  for (int i = 2; i >= 0; --i) {
    preserve_bit = value->bits[i] % 2;
    value->bits[i] >>= 1;
    value->bits[i] += preserve_bit_prev << 31;
    preserve_bit_prev = preserve_bit;
  }
}

int mul_int_ten(s21_decimal value, s21_decimal *result) {
  s21_decimal ten = {{10, 0, 0, 0}};
  int r = s21_mul_int(value, ten, result);
  if (!r) result->bits[3] = value.bits[3];
  return r;
}

void s21_from_decimal_to_long_decimal(s21_decimal src, s21_long_decimal *dst) {
  for (int i = 0; i < BITS_SIZE - 1; i++) dst->bits[i] = src.bits[i];
  for (int i = BITS_SIZE - 1; i < BITS_SIZE_LONG - 1; i++) dst->bits[i] = 0;
  dst->bits[BITS_SIZE_LONG - 1] = src.bits[BITS_SIZE - 1];
}

int convert_long_decimal_to_decimal(s21_long_decimal sum, s21_decimal *result) {
  int r = 0;
  s21_decimal temp;

  temp.bits[3] = sum.bits[6];
  int i;
  for (i = 0; i < 3; i++) temp.bits[i] = sum.bits[i];
  while (i < 6 && sum.bits[i] == 0) i++;
  if (i != 6) {
    r = 1;
  } else {
    for (int i = 0; i < 4; i++) result->bits[i] = temp.bits[i];
  }

  return r;
}

int s21_from_long_decimal_to_decimal(s21_long_decimal src, s21_decimal *dst) {
  int r = 0;
  s21_long_decimal n = {{0}}, f = {{0}};
  int sign = get_sign_long(src);
  set_sign_long(&src, 0);
  remove_trailing_zeroes_long(&src);
  s21_truncate_long(src, &n);
  if (s21_is_less_or_equal_long_int(n, LONG_DECIMAL_DECIMAL_MAX)) {
    s21_long_decimal norm_n = n;
    s21_normalize_long(&norm_n, &src);
    s21_sub_long(src, norm_n, &f);
    set_exp_long(&f, get_exp_long(src));
    reduce_until_addable(n, f, dst);
    set_sign(dst, sign);
  } else {
    r = 1;
  }

  return r;
}

int try_adding(s21_long_decimal z, s21_long_decimal q, s21_decimal *result) {
  int e = get_exp_long(q);
  int r = 0;
  s21_normalize_long(&z, &q);
  s21_add_long(z, q, &z);
  set_exp_long(&z, e);
  if (convert_long_decimal_to_decimal(z, result) == 0) {
    r = 1;
  }

  return r;
}

int reduce_until_addable(s21_long_decimal z, s21_long_decimal q,
                         s21_decimal *result) {
  int r = 0;
  int i = get_exp_long(q);
  s21_long_decimal nq = q;
  while (!try_adding(z, nq, result) || i > 28) {
    --i;
    s21_bank_round_n_long(q, &nq, i);
  }
  return r;
}

void print_dec(s21_decimal value) {
  for (int i = 0; i < BITS_SIZE - 1; ++i) {
    printf(" %d", value.bits[i]);
  }
  printf(" |%d\n", value.bits[BITS_SIZE - 1]);
}

void print_dec_long(s21_long_decimal value) {
  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    printf(" %u", value.bits[i]);
  }
  printf(" |%u\n", value.bits[BITS_SIZE_LONG - 1]);
}
