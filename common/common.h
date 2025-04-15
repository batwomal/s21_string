#ifndef COMMN_H
#define COMMN_H

#ifndef S21_SIZE_T
#define S21_SIZE_T

typedef unsigned long int s21_size_t;

#endif

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void s21_error(const char *pname, const char *message);
void *s21_calloc(s21_size_t size);
void *s21_realloc(void *memblock, s21_size_t size);

char *s21_strdup(const char *str);

int s21_atoi(const char *str);

#endif
