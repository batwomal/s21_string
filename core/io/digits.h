#ifndef DIGITS_H
#define DIGITS_H

#include <float.h>
#include <limits.h>
#include <math.h>

typedef short int si;
typedef unsigned short int usi;
typedef unsigned int uint;
typedef long int li;
typedef unsigned long int uli;
typedef long long int lli;
typedef unsigned long long int ulli;

typedef long double long_double;

#define POW(x, y) \
  _Generic((x), float: powf, double: pow, long double: powl)(x, y)

#define MODF(x, y) \
  _Generic((x), float: modff, double: modf, long double: modfl)(x, y)

#define FMOD(x, y) \
  _Generic((x), float: fmodf, double: fmod, long double: fmodl)(x, y)

#define FABS(x) _Generic((x), float: fabsf, double: fabs, long double: fabsl)(x)

#define RINT(x) _Generic((x), float: rintf, double: rint, long double: rintl)(x)

#define FLOOR(x) \
  _Generic((x), float: floorf, double: floor, long double: floorl)(x)

#define LOG10(x) \
  _Generic((x), float: log10f, double: log10, long double: log10l)(x)

char *s21_itoa_si(short i, char *str);
char *s21_itoa_usi(unsigned short int i, char *str, int base);
char *s21_itoa_int(int i, char *str);
char *s21_itoa_uint(unsigned int i, char *str, int base);
char *s21_itoa_li(long int i, char *str);
char *s21_itoa_uli(unsigned long int i, char *str, int base);
char *s21_itoa_lli(long long int i, char *str);
char *s21_itoa_ulli(unsigned long long int i, char *str, int base);

#define S21_ITOA(x, y, z)                    \
  _Generic((x),                              \
      short: s21_itoa_si(x, y),              \
      unsigned short: s21_itoa_usi(x, y, z), \
      int: s21_itoa_int(x, y),               \
      unsigned int: s21_itoa_uint(x, y, z),  \
      long: s21_itoa_li(x, y),               \
      unsigned long: s21_itoa_uli(x, y, z),  \
      long long: s21_itoa_lli(x, y),         \
      unsigned long long: s21_itoa_ulli(x, y, z))

char *s21_ftoa_double(char *out_str, double num, int precision);
char *s21_ftoa_long_double(char *out_str, long double num, int precision);

#define S21_FTOA(x, y, z)                      \
  _Generic((y),                                \
      float: s21_ftoa_double(x, (double)y, z), \
      double: s21_ftoa_double(x, y, z),        \
      long double: s21_ftoa_long_double(x, y, z))

char *s21_exptoa_double(char *out_str, double num, int precision);
char *s21_exptoa_long_double(char *out_str, long double num, int precision);

#define S21_EXPTOA(x, y, z)                      \
  _Generic((y),                                  \
      float: s21_exptoa_double(x, (double)y, z), \
      double: s21_exptoa_double(x, y, z),        \
      long double: s21_exptoa_long_double(x, y, z))

#endif