#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  if (src < 0) {
    dst->bits[3] |= (1 << 31);
    src = -src;
  }
  dst->bits[0] = src;
  return 0;
}
