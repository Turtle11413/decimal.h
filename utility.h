#ifndef S21_DECIMAL_UTILITY_H_
#define S21_DECIMAL_UTILITY_H_

#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "s21_decimal.h"

typedef struct {
  unsigned int bits[7];
} s21_long_decimal;

#define BITS_SIZE 4
#define BITS_SIZE_LONG 7
#define MUL_RESERVE 6
#define SIGN_MASK (1 << 31)
#define EXP_MASK (255 << 16)
#define VAL_MASK (SIGN_MASK | EXP_MASK)
#define UINT_MAX 4294967295
#define DECIMAL_MAX                     \
  {                                     \
    { UINT_MAX, UINT_MAX, UINT_MAX, 0 } \
  }
#define EXP_MAX 28
#define DECIMAL_TEN \
  {                 \
    { 10, 0, 0, 0 } \
  }
#define MAXINT 2147483647
#define MININT -2147483648
#define LONG_DECIMAL_DECIMAL_MAX                 \
  (s21_long_decimal) {                           \
    { UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0 } \
  }

int s21_is_greater_or_equal_long(s21_long_decimal, s21_long_decimal);
int s21_is_less_or_equal_long(s21_long_decimal value_1,
                              s21_long_decimal value_2);
int s21_is_less_long(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_is_equal_long(s21_long_decimal value_1, s21_long_decimal value_2);

int s21_is_equal_long_int(s21_long_decimal, s21_long_decimal);
int s21_is_greater_or_equal_long_int(s21_long_decimal, s21_long_decimal);
int s21_is_greater_or_equal_int(s21_long_decimal, s21_long_decimal);
int s21_is_less_long_int(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_is_less_or_equal_long_int(s21_long_decimal, s21_long_decimal);

int s21_add_long(s21_long_decimal value_1, s21_long_decimal value_2,
                 s21_long_decimal *result);

int s21_sub_long(s21_long_decimal value_1, s21_long_decimal value_2,
                 s21_long_decimal *result);
int s21_sub_long_int(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result);

int s21_mul_int(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_mul_int_long(s21_long_decimal value1, s21_long_decimal value2,
                     s21_long_decimal *result);

void s21_div_long(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result, int *result_exp);
void s21_div_ten(s21_decimal value_1, s21_decimal *result);
int s21_div_ten_long(s21_long_decimal value_1, s21_long_decimal *result);

int s21_floor_long(s21_long_decimal src, s21_long_decimal *dst);

int s21_round_n_long(s21_long_decimal src, s21_long_decimal *dst, int n);
int s21_bank_round_n_long(s21_long_decimal src, s21_long_decimal *dst, int n);
int s21_round_n(s21_decimal src, s21_decimal *dst, int n);

int s21_truncate_long(s21_long_decimal value, s21_long_decimal *result);

int convert_long_decimal_to_decimal(s21_long_decimal sum, s21_decimal *result);

int s21_from_long_decimal_to_decimal(s21_long_decimal src, s21_decimal *dst);
void s21_from_decimal_to_long_decimal(s21_decimal src, s21_long_decimal *dst);

int get_exp(s21_decimal value);
int get_sign(s21_decimal value);
void set_exp(s21_decimal *value, int exp);
void set_sign(s21_decimal *value, int sign);
void move_decimal_right(s21_decimal *value);
int mul_int_ten(s21_decimal value, s21_decimal *result);

int get_exp_long(s21_long_decimal value);
int get_sign_long(s21_long_decimal value);
void set_exp_long(s21_long_decimal *value, int exp);
void set_sign_long(s21_long_decimal *value, int sign);
void move_long_decimal_left(s21_long_decimal *offset);
void move_long_decimal_right(s21_long_decimal *offset);
int mul_int_ten_long(s21_long_decimal value, s21_long_decimal *result);
void s21_normalize_long(s21_long_decimal *value1, s21_long_decimal *value2);
void remove_trailing_zeroes_long(s21_long_decimal *val);
int s21_mod_ten_long(s21_long_decimal val);
int reduce_until_addable(s21_long_decimal z, s21_long_decimal q,
                         s21_decimal *result);
int s21_is_null_long(s21_long_decimal value1);

void print_dec(s21_decimal a);
void print_dec_long(s21_long_decimal a);

#endif
