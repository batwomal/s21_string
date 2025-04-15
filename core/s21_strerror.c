#include "../s21_errors.h"
#include "../s21_string.h"

char *s21_strerror(int errnum) {
  char *errors[] = S21_ERROR_MESSAGES;
  char *result = S21_NULL;
  static char number[64] = {0};

  if (errnum >= 0 && errnum < S21_ERRORS_CONUT) {
    result = errors[errnum];
  } else {
    s21_sprintf(number, "Unknown error %d", errnum);
    result = number;
  }
  return result;
}
