#include "../../s21_string.h"

#define MIN_si SHRT_MIN
#define MIN_STR_si "-32768"
#define MIN_usi (0)
#define MIN_STR_usi "0"
#define MIN_int INT_MIN
#define MIN_STR_int "-2147483648"
#define MIN_uint (0)
#define MIN_STR_uint "0"
#define MIN_li LONG_MIN
#define MIN_STR_li "-9223372036854775808"
#define MIN_uli (0)
#define MIN_STR_uli "0"
#define MIN_lli LLONG_MIN
#define MIN_STR_lli "-9223372036854775808"
#define MIN_ulli (0)
#define MIN_STR_ulli "0"

#define MIN(x) MIN_##x

#define MIN_STR(x) MIN_STR_##x

#define S21_ITOA_COMMON_(type)                                    \
  char* s21_itoa_##type(type i, char* str) {                      \
    char* p = str;                                                \
    if (i == MIN(type))                                           \
      s21_strncat(str, MIN_STR(type), s21_strlen(MIN_STR(type))); \
    else {                                                        \
      if (i < 0) {                                                \
        *p++ = '-';                                               \
        i *= -1;                                                  \
      }                                                           \
      char const digit[] = "0123456789";                          \
      type shifter = i;                                           \
      do {                                                        \
        ++p;                                                      \
      } while (shifter /= 10);                                    \
      *p = '\0';                                                  \
      do {                                                        \
        *--p = digit[i % 10];                                     \
      } while (i /= 10);                                          \
    }                                                             \
    return str;                                                   \
  }

#define S21_ITOA_UNSIGNED_COMMON_(type)                           \
  char* s21_itoa_##type(type i, char* str, int base) {            \
    char* p = str;                                                \
    if (i == MIN(type))                                           \
      s21_strncat(str, MIN_STR(type), s21_strlen(MIN_STR(type))); \
    else {                                                        \
      char const digit[] = "0123456789abcdef";                    \
      type shifter = i;                                           \
      do {                                                        \
        ++p;                                                      \
      } while (shifter /= base);                                  \
      *p = '\0';                                                  \
      do {                                                        \
        *--p = digit[i % base];                                   \
      } while (i /= base);                                        \
    }                                                             \
    return str;                                                   \
  }

S21_ITOA_COMMON_(si)
S21_ITOA_UNSIGNED_COMMON_(usi)
S21_ITOA_COMMON_(int)
S21_ITOA_UNSIGNED_COMMON_(uint)
S21_ITOA_COMMON_(li)
S21_ITOA_UNSIGNED_COMMON_(uli)
S21_ITOA_COMMON_(lli)
S21_ITOA_UNSIGNED_COMMON_(ulli)
