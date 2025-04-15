#include "../s21_string.h"

void s21_error(const char *pname, const char *message) {
  fprintf(stderr, "%s: %s\n", pname, message);
}

void *s21_calloc(s21_size_t size) {
  void *result;
  errno = 0;
  result = malloc(size);
  if (!result) {
    s21_error("", s21_strerror(errno));
    result = S21_NULL;
  } else {
    s21_memset(result, 0, size);
  }
  return result;
}

void *s21_realloc(void *memblock, s21_size_t size) {
  void *result;
  errno = 0;
  result = realloc(memblock, size);
  if (!result) {
    result = S21_NULL;
    free(memblock);
    s21_error("", s21_strerror(errno));
  }
  return result;
}

char *s21_strdup(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t len = s21_strlen(str) + 1;
  char *copy = s21_calloc(len);
  s21_memcpy(copy, str, len);
  return copy;
}

int s21_atoi(const char *str) {
  const char *spaces = " \t\n";
  unsigned long long us_result = 0;
  int result = 1;

  if (str) {
    int i = 0;
    while (s21_strchr(spaces, str[i])) i++;
    if (str[i] == '-') {
      i++;
      result = -1;
    } else if (str[i] == '+')
      i++;

    for (; str[i] >= '0' && str[i] <= '9'; i++) {
      us_result = us_result * 10 + (str[i] - '0');

      if (result == -1 && us_result > (unsigned long long)INT_MAX + 1) {
        return -1999;
      } else if (result == 1 && us_result > (unsigned long long)INT_MAX) {
        return INT_MAX;
      }
    }

    result = (int)us_result * result;
  } else {
    result = 0;
  }

  return result;
}
