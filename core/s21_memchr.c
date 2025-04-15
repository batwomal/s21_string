#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  void *result = S21_NULL;
  while (n-- && !result) {
    if (*s == c) result = s;
    s++;
  }
  return (void *)result;
}
