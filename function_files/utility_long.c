#include "../s21_decimal.h"
#include "../utility.h"

void s21_normalize_long(s21_long_decimal *value1, s21_long_decimal *value2) {
  s21_long_decimal *values[2] = {value1, value2};
  int exp1 = get_exp_long(*value1);
  int exp2 = get_exp_long(*value2);
  int diff, c;
  if (exp1 == exp2) {
    c = 0;
    diff = 0;
  } else if (exp1 > exp2) {
    c = 1;
    diff = exp1 - exp2;
  } else {
    c = 0;
    diff = exp2 - exp1;
  }
  for (int i = 0; i < diff; i++) {
    mul_int_ten_long(*values[c], values[c]);
  }
  set_exp_long(values[c], get_exp_long(*values[c]) + diff);
}

int get_exp_long(s21_long_decimal value) {
  return ((value.bits[6] & EXP_MASK) >> 16);
}

int get_sign_long(s21_long_decimal value) {
  return ((value.bits[6] & SIGN_MASK) >> 31);
}

void set_exp_long(s21_long_decimal *value, int exp) {
  value->bits[6] &= ~EXP_MASK;
  value->bits[6] += exp << 16;
}

void set_sign_long(s21_long_decimal *value, int sign) {
  value->bits[6] &= ~SIGN_MASK;
  value->bits[6] += sign << 31;
}

int mul_int_ten_long(s21_long_decimal value, s21_long_decimal *result) {
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  int r = s21_mul_int_long(value, ten, result);
  if (!r) result->bits[6] = value.bits[6];
  return r;
}

void move_long_decimal_left(s21_long_decimal *offset) {
  int preserve_bit, preserve_bit_prev = 0;
  for (int i = 0; i < MUL_RESERVE; ++i) {
    preserve_bit = (offset->bits[i] & SIGN_MASK) >> 31;
    offset->bits[i] <<= 1;
    offset->bits[i] += preserve_bit_prev;
    preserve_bit_prev = preserve_bit;
  }
}

void move_long_decimal_right(s21_long_decimal *offset) {
  int preserve_bit, preserve_bit_prev = 0;
  for (int i = MUL_RESERVE - 1; i >= 0; --i) {
    preserve_bit = offset->bits[i] % 2;
    offset->bits[i] >>= 1;
    offset->bits[i] += preserve_bit_prev << 31;
    preserve_bit_prev = preserve_bit;
  }
}

int s21_mod_ten_long(s21_long_decimal val) {
  s21_long_decimal dec_n = {{0}};
  s21_long_decimal temp = {{0}};

  val.bits[BITS_SIZE_LONG - 1] = 0;
  s21_div_ten_long(val, &temp);
  mul_int_ten_long(temp, &temp);
  s21_sub_long_int(val, temp, &dec_n);

  return dec_n.bits[0];
}

void remove_trailing_zeroes_long(s21_long_decimal *val) {
  int i = 0;
  int e = get_exp_long(*val);
  while (s21_mod_ten_long(*val) == 0 && i < e) {
    s21_long_decimal temp = {{0}};
    s21_div_ten_long(*val, &temp);
    *val = temp;
    ++i;
  }
  set_exp_long(val, e - i);
}

int s21_is_null_long(s21_long_decimal value1) {
  int r = 1;
  for (int i = 0; i < BITS_SIZE_LONG - 1; ++i) {
    if (value1.bits[i] != 0) {
      r = 0;
      i = BITS_SIZE_LONG;
    }
  }
  return r;
}
