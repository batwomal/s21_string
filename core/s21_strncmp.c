#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (const char *ptr1 = str1, *ptr2 = str2;
       (s21_size_t)(ptr1 - str1) < n && !result; ptr1++, ptr2++)
    if (*ptr1 != *ptr2) result = *ptr1 - *ptr2;
  return result;
}