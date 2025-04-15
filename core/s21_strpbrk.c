#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 && str2) {
    while (*str1 && !result) {
      char *cur2 = (char *)str2;
      while (*cur2 && !result) {
        if (*str1 == *cur2) result = (char *)str1;
        cur2++;
      }
      str1++;
    }
  }
  return result;
}