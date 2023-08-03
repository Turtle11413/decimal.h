#include "../s21_decimal.h"
#include "../utility.h"

int try_adding(s21_long_decimal z, s21_long_decimal q, s21_decimal *result);
int single_digit_multiplication(s21_long_decimal *sum, s21_long_decimal *offset,
                                int carry);

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  int r = 0;
  s21_long_decimal v1l, v2l, rl;

  s21_from_decimal_to_long_decimal(value1, &v1l);
  s21_from_decimal_to_long_decimal(value2, &v2l);
  s21_mul_int_long(v1l, v2l, &rl);
  set_exp_long(&rl, get_exp(value1) + get_exp(value2));
  r = s21_from_long_decimal_to_decimal(rl, result);

  return r;
}

int s21_mul_int(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  int r = 0;
  s21_long_decimal offset = {
      {value1.bits[0], value1.bits[1], value1.bits[2], 0, 0, 0, 0}};
  s21_long_decimal sum = {{0, 0, 0, 0, 0, 0, 0}};

  // multiplication part
  for (int bit = 0; bit < 32 * 3; ++bit) {
    unsigned int multiplier;
    unsigned int carry = 0;
    multiplier = value2.bits[bit / 32] % 2;
    // sum
    if (multiplier) {
      carry = single_digit_multiplication(&sum, &offset, carry);
    }
    // verh << 1
    move_long_decimal_left(&offset);
    // niz >> 1
    value2.bits[bit / 32] >>= 1;
  }

  int sign = get_sign(value1) ^ get_sign(value2);
  sum.bits[6] += sign << 31;
  r = convert_long_decimal_to_decimal(sum, result);

  return r;
}

int s21_mul_int_long(s21_long_decimal value1, s21_long_decimal value2,
                     s21_long_decimal *result) {
  int r = 0;
  s21_long_decimal offset = value1;
  s21_long_decimal sum = {{0, 0, 0, 0, 0, 0, 0}};

  // multiplication part
  for (int bit = 0; bit < 32 * MUL_RESERVE; ++bit) {
    unsigned int multiplier;
    unsigned int carry = 0;
    multiplier = value2.bits[bit / 32] % 2;
    // sum
    if (multiplier) {
      carry = single_digit_multiplication(&sum, &offset, carry);
    }
    // verh << 1
    move_long_decimal_left(&offset);
    // niz >> 1
    value2.bits[bit / 32] >>= 1;
  }

  int sign = get_sign_long(value1) ^ get_sign_long(value2);
  set_sign_long(&sum, sign);
  for (int i = 0; i < 7; i++) result->bits[i] = sum.bits[i];

  return r;
}

int single_digit_multiplication(s21_long_decimal *sum, s21_long_decimal *offset,
                                int carry) {
  for (int i = 0; i < MUL_RESERVE; ++i) {
    // overflow case
    if (sum->bits[i] > UINT_MAX - offset->bits[i]) {
      unsigned int max =
          sum->bits[i] > offset->bits[i] ? sum->bits[i] : offset->bits[i];
      unsigned int min =
          sum->bits[i] < offset->bits[i] ? sum->bits[i] : offset->bits[i];
      sum->bits[i] = min - (UINT_MAX - max) - 1 + carry;
      carry = 1;
    } else {
      sum->bits[i] += offset->bits[i] + carry;
      carry = 0;
    }
  }
  return carry;
}
