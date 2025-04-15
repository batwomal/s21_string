#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *line1 = (unsigned char *)str1;
  unsigned char *line2 = (unsigned char *)str2;
  int result = 0;
  if ((line1 && line2)) {
    for (unsigned char *ptr1 = line1, *ptr2 = line2;
         (s21_size_t)(ptr1 - line1) < n && !result; ptr1++, ptr2++)
      if (*ptr1 != *ptr2) result = *ptr1 - *ptr2;
  }
  return result;
}