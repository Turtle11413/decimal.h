#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  value.bits[3] ^= (1 << 31);
  *result = value;

  return 0;
}