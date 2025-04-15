#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str != S21_NULL) {
    unsigned char *ptr = (unsigned char *)str;
    while (n--) *ptr++ = c;
  }
  return str;
}