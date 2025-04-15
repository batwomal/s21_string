#include "../../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed_str = S21_NULL;
  if (src != S21_NULL || trim_chars != S21_NULL) {
    s21_size_t len = s21_strlen(src);
    if (len > 0) {
      s21_size_t start = 0;
      while (start < len && s21_strchr(trim_chars, src[start]) != S21_NULL)
        start++;

      s21_size_t end = len - 1;
      while (end >= start && s21_strchr(trim_chars, src[end]) != S21_NULL)
        end--;

      if (start > end) {
        trimmed_str = s21_strdup("");
      } else {
        s21_size_t trimmed_len = end - start + 1;
        trimmed_str = (char *)s21_realloc(trimmed_str, trimmed_len + 1);
        s21_memcpy(trimmed_str, src + start, trimmed_len);
        trimmed_str[trimmed_len] = '\0';
      }
    } else
      trimmed_str = s21_strdup("");
  } else
    trimmed_str = S21_NULL;
  return trimmed_str;
}
