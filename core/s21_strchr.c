#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  if (str) {
    while (*str != '\0' && !result) {
      if (*str == (char)c) result = (char *)str;
      str++;
    }
    if (c == '\0') result = (char *)str;
  }
  return result;
}