#include "../../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL || s21_strlen(src) < start_index)
    return S21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  char *result = (char *)s21_calloc(src_len + str_len + 1);

  s21_memcpy(result, src, start_index);
  s21_memcpy(result + start_index, str, str_len);
  s21_memcpy(result + start_index + str_len, src + start_index,
             src_len - start_index + 1);

  return (void *)result;
}
