#include <math.h>

#include "../../s21_string.h"
#include "digits.h"

int print_special_numbers(char *out_str, long double num, int precision) {
  int res = 0;
  if (isnan(num)) {
    s21_strncat(out_str, "nan", 3);
    res = 1;
  } else if (isinf(num) && num > 0) {
    s21_strncat(out_str, "inf", 3);
    res = 1;
  } else if (isinf(num) && num < 0) {
    s21_strncat(out_str, "-inf", 4);
    res = 1;
  } else if (num == 0) {
    if (signbit(num)) s21_strncat(out_str, "-", 1);
    s21_strncat(out_str, "0", 1);
    if (precision > 0) {
      s21_strncat(out_str, ".", 1);
      while (precision--) s21_strncat(out_str, "0", 1);
    }
    res = 1;
  }
  return res;
}

char *handle_two_dots(char *s) {
  s21_size_t cnt = 0;
  int sign = *s == '-';

  while (*(s + 1)) {
    cnt++;
    s++;
  }
  while ((*s == ':' || *s == '/') && (cnt - sign)) {
    if (*(s) == '/')
      *s = '.';
    else
      *s = '0';
    if (*(s - 1) != '-') (*--s)++;
    cnt--;
  }
  if (*s == ':') {
    *s = '0';
    char *temp = s21_insert(s, "1", 0);
    s = s21_memcpy(s, temp, s21_strlen(temp) + 1);
    free(temp);
  }

  return s;
}

char *float_round(char *str, long double num) {
  char *ptr = str;
  num = MODF(num * 10, &num);
  const char *point = s21_strrchr(str, '.');
  while (*(ptr++)) {
    ;
  }
  ptr -= (s21_strlen(str) != 1);
  if (num >= 0.5) {
    *ptr = 0;
    ptr--;
    if (((*(ptr) - '0') % 2 != 0) && num - 0.5 < FLT_EPSILON)
      (*ptr)++;
    else if (num > 0.5)
      (*ptr)++;
    handle_two_dots(str);
  } else {
    *ptr-- = 0;
  }
  if (s21_strlen(point) == 1) *(ptr) = 0;
  return str;
}

#define PRINT_FRACPART(type)                                                 \
  char *print_fracpart_##type(char *out_str, type *num, int precision) {     \
    char buffer[5000] = {0};                                                 \
    char *s = buffer;                                                        \
    *num = MODF(*num, num);                                                  \
    type temp = *num;                                                        \
    while (precision--) {                                                    \
      temp *= 10;                                                            \
      if (precision > 0)                                                     \
        *s++ = (int)FMOD(temp, 10) + '0';                                    \
      else {                                                                 \
        *s = (int)(FMOD(temp, 10)) + '0';                                    \
        /*s = handle_two_dots(s);                                         */ \
        s++;                                                                 \
      }                                                                      \
    }                                                                        \
    *num = MODF(temp / 10, &temp);                                           \
    s21_strncat(out_str, buffer, s - buffer);                                \
    return out_str;                                                          \
  }

#define PRINT_INTPART(type)                                            \
  char *print_intpart_##type(char *out_str, type num, int precision) { \
    char buffer[5000] = {0};                                           \
    char *s = buffer;                                                  \
    if (!precision) num = RINT(num);                                   \
    type ten = (type)10;                                               \
    type temp = num;                                                   \
    int num_cnt = 0;                                                   \
    if (num < 1.0)                                                     \
      *s++ = '0';                                                      \
    else {                                                             \
      while (temp >= 1.0) {                                            \
        num_cnt++;                                                     \
        temp /= 10;                                                    \
      }                                                                \
      temp = num;                                                      \
      while (num_cnt) {                                                \
        long double pow_t = POW(ten, num_cnt);                         \
        long double result = FMOD(num, pow_t);                         \
        if (num_cnt > 1 || precision)                                  \
          *s = (int)(result / (pow_t / ten)) + '0';                    \
        else if (precision <= 1) {                                     \
          *s = (int)RINT(result / (pow_t / ten)) + '0';                \
          handle_two_dots(buffer);                                     \
        }                                                              \
        s++;                                                           \
        num_cnt--;                                                     \
      }                                                                \
    }                                                                  \
    /**s = '\0'; */                                                    \
    s21_strncat(out_str, buffer, s - buffer);                          \
    return out_str;                                                    \
  }

PRINT_INTPART(double)
PRINT_INTPART(long_double)

PRINT_FRACPART(double)
PRINT_FRACPART(long_double)

#define S21_FTOA_COMMON(type)                                     \
  char *s21_ftoa_##type(char *out_str, type num, int precision) { \
    if (!print_special_numbers(out_str, num, precision)) {        \
      /*precision += 4;*/                                         \
      if (signbit(num)) s21_strncat(out_str, "-", 1);             \
      num = FABS(num);                                            \
      print_intpart_##type(out_str, num, precision);              \
      if (precision > 0) {                                        \
        s21_strncat(out_str, ".", 1);                             \
        print_fracpart_##type(out_str, &num, precision);          \
        out_str = float_round(out_str, num);                      \
      }                                                           \
    }                                                             \
    return out_str;                                               \
  }

S21_FTOA_COMMON(double)
S21_FTOA_COMMON(long_double)

#define S21_EXPTOA_COMMON(type)                                     \
  char *s21_exptoa_##type(char *out_str, type num, int precision) { \
    if (!print_special_numbers(out_str, num, precision) || !num) {  \
      if (signbit(num) && num) s21_strncat(out_str, "-", 1);        \
      num = FABS(num);                                              \
      int exp = 0;                                                  \
      if (num) exp = (int)FLOOR(LOG10(num));                        \
      type ten = (type)10;                                          \
      num /= POW(ten, exp);                                         \
      if (FABS(num / ten - 1.0) < FLT_EPSILON) {                    \
        num /= ten;                                                 \
        exp++;                                                      \
      }                                                             \
      if (num) S21_FTOA(out_str, num, precision);                   \
      s21_sprintf(out_str, "e%+.2d", exp);                          \
    }                                                               \
    return out_str;                                                 \
  }

S21_EXPTOA_COMMON(double)
S21_EXPTOA_COMMON(long_double)