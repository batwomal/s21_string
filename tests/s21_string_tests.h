#ifndef S21_STRING_TESTS_H_
#define S21_STRING_TESTS_H_

#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

#define BUF_SIZE 8192

int test_s21_sprintf(void);
int test_s21_sscanf(void);

int test_common(void);
int test_s21_atoi(void);
int test_s21_llitoa(void);
int test_s21_lftoa(void);
int test_s21_lftoa_large(void);
int test_s21_exptoa(void);

int test_spec_c(void);

int test_s21_memset(void);
int test_s21_memcpy(void);
int test_s21_memchr(void);
int test_s21_memcmp(void);

int test_s21_strlen(void);
int test_s21_strchr(void);
int test_s21_strrchr(void);
int test_s21_strpbrk(void);
int test_s21_strncpy(void);
int test_s21_strncat(void);
int test_s21_strerror(void);
int test_s21_strcspn(void);
int test_s21_strstr(void);
int test_s21_strncmp(void);
int test_s21_strtok(void);

int test_s21_insert(void);
int test_s21_trim(void);
int test_s21_to_upper(void);
int test_s21_to_lower(void);

int test_parse_format(void);
#endif