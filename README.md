# decimal.h

## Binary representation
Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).
`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.
`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15 are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

## Example
```c
typedef struct 
{
    int bits[4];
} decimal;
```

## Install
```bash
git clone git@github.com:Turtle11413/decimal.h.git
cd decimal.h
```

## Build
```bash
make s21_decimal.a
```
