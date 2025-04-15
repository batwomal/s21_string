#include "s21_string_tests.h"

int main() {
  int failed_count = 0;

  failed_count += test_s21_sprintf();
  failed_count += test_s21_sscanf();
  failed_count += test_parse_format();

  failed_count += test_common();
  failed_count += test_s21_atoi();
  failed_count += test_s21_llitoa();
  // failed_count += test_s21_lftoa();
  // failed_count += test_s21_lftoa_large();
  // failed_count += test_s21_exptoa();

  failed_count += test_spec_c();

  failed_count += test_s21_memset();
  failed_count += test_s21_memcpy();
  failed_count += test_s21_memcmp();
  failed_count += test_s21_memchr();

  failed_count += test_s21_strlen();
  failed_count += test_s21_strchr();
  failed_count += test_s21_strrchr();
  failed_count += test_s21_strpbrk();
  failed_count += test_s21_strncpy();
  failed_count += test_s21_strncat();
  failed_count += test_s21_strerror();
  failed_count += test_s21_strcspn();
  failed_count += test_s21_strstr();
  failed_count += test_s21_strncmp();
  failed_count += test_s21_strtok();

  failed_count += test_s21_insert();
  failed_count += test_s21_trim();
  failed_count += test_s21_to_upper();
  failed_count += test_s21_to_lower();

  printf("TOTAL FAILED: %d\n\n\n", failed_count);
  return 0;
}