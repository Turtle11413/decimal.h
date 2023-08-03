#include "../s21_decimal.h"
#include "../utility.h"

int s21_from_decimal_to_float(s21_decimal value, float* dst) {
  int return_value = 0;

  if ((dst == NULL) || (get_exp(value) > 28)) {
    *dst = 0;
    return_value = 0;
  } else {
    int sign = get_sign(value);
    int exp = get_exp(value);
    double res = 0;

    for (int bit = 0; bit < 32 * 3; ++bit) {
      res += pow(2, bit) * (value.bits[0] % 2);
      move_decimal_right(&value);
    }

    res *= sign == 1 ? -1 : 1;
    res /= pow(10, exp);

    *dst = (float)res;
  }

  return return_value;
}
