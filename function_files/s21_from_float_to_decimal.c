#include "../s21_decimal.h"
#include "../utility.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ret = 0;
  if (src == 1.0F / 0.0F || src == -1.0 / 0.0F || src != src) {
    s21_from_int_to_decimal(0, dst);
    ret = 1;
  } else {
    char fstr[64];
    int fdig[64] = {0};
    int exp = 0;
    int exp_sign = 0;
    char *c;
    int z_dig = 0;
    int q_dig = 0;
    int significants = 0;
    int dig_num = 0;
    int is_q = 0;
    int sign = src < 0 ? 1 : 0;
    s21_decimal undivided = {{0}};
    s21_decimal divisor = {{10, 0, 0, 0}};

    s21_from_int_to_decimal(0, dst);
    src = src < 0 ? -src : src;
    sprintf(fstr, "%.6e", src);

    for (c = fstr; *c != 'e' && *c != 'E'; ++c) {
      if (*c >= '0' && *c <= '9') {
        fdig[dig_num++] = *c - 0x30;
        if (is_q) {
          ++q_dig;
          if (*c != '0') significants = q_dig;
        } else
          ++z_dig;
      } else if (*c == '.') {
        is_q = 1;
      }
    }
    ++c;
    exp_sign = *(c++) == '+' ? 0 : 1;
    exp = (*(c++) - 0x30) * 10;
    exp += *(c++) - 0x30;

    for (int i = 0; i < z_dig + significants; ++i) {
      mul_int_ten(undivided, &undivided);
      s21_decimal dec_n;
      s21_from_int_to_decimal(fdig[i], &dec_n);
      s21_add(dec_n, undivided, &undivided);
    }
    set_exp(&undivided, significants);
    for (int i = 0; i < exp - 1; ++i) mul_int_ten(divisor, &divisor);
    if (exp_sign) {
      s21_div(undivided, divisor, dst);
    } else {
      s21_mul(undivided, divisor, dst);
    }
    set_sign(dst, sign);
  }

  return ret;
}
