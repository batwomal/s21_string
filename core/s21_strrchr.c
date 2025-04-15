#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  const char *start = str;
  if (*start) {
    int B = 0;
    while (*str) {
      if (*str == c) {
        result = (char *)str;
        B++;
      }
      str++;
    }
    if (B == 0 && c == '\0') result = (char *)str;
  }
  return result;
}