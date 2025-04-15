#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *ptr = str;
  s21_size_t cnt = 0;
  if (str)
    while (*ptr != '\0') {
      ptr++;
      cnt++;
    }
  return cnt;
}