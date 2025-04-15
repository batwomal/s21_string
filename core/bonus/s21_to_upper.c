#include "../../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  char *result = s21_strdup(str);
  char *tmp = result;
  while (*tmp) {
    if (*tmp >= 'a' && *tmp <= 'z') *tmp -= 32;
    tmp++;
  }
  return (void *)result;
}