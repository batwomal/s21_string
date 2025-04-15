#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;

  if (str == S21_NULL) {
    return S21_NULL;
  } else
    next_token = str;

  char *start = next_token;

  while (*start && s21_strchr(delim, *start)) {
    start++;
  }

  if (*start == '\0') {
    next_token = S21_NULL;
    return S21_NULL;
  }

  char *end = start;
  while (*end && !s21_strchr(delim, *end)) {
    end++;
  }

  if (*end) {
    *end = '\0';
    next_token = end + 1;
  } else {
    next_token = S21_NULL;
  }

  return start;
}
