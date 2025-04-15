#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include "../../s21_string.h"

#define BUF_SIZE 8192

typedef struct specs {
  char spec;
  int precision;
  int width;
  char flag[5];
  /*
    flag[0] - '-'
    flag[1] - '+'
    flag[2] - ' '
    flag[3] - '#'
    flag[4] - '0'
  */
  char length[3];
  /*
    length[0] - 'h'
    length[1] - 'l'
    length[2] - 'L'
  */
} specs;

int process_specs(va_list *args, char **cursor, const specs *options);
specs *parse_format(const char **format, va_list *args);
int set_default_precision(int precision, char spec);
int spec_c(char value, const specs *options, char **cursor);
int spec_s(const char *value, const specs *options, char **cursor);
int spec_percent(char **cursor);

int spec_ints(long long int value, int base, const specs *options,
              char **cursor);
int spec_p(void *value, specs *options, char **cursor);

int spec_f(long double value, specs *options, char **cursor);

int spec_e_long_double(long double value, const specs *options, char **cursor);
int spec_e_double(double value, const specs *options, char **cursor);

#define SPEC_E(x, y, z) \
  _Generic((x), long double: spec_e_long_double, double: spec_e_double)(x, y, z)

int spec_g(long double value, specs *options, char **cursor);
int spec_g_precision(long double value, int precision, const specs *options);
int spec_g_cnt_digits(long double value);
char determine_sign_char(char *number, const specs *options);
int calculate_precision_padding(int len, const specs *options, char *number);
int calculate_width_padding(int total_len, const specs *options);
void handle_flag_minus(char **temp_ptr, const char *number, int len,
                       int precision_padding, int width_padding,
                       char sign_char);
void handle_flag_zero(char **temp_ptr, const char *number, int len,
                      int width_padding, char sign_char);
void handle_default(char **temp_ptr, const char *number, int len,
                    int precision_padding, int width_padding, char sign_char);
void add_prefix_for_flag_hash(char **number, const specs *options,
                              int precision_padding);
void handle_flag_hash(char **number, const specs *options, int *len,
                      int precision_padding);
void move_prefix_to_start(char *str);
char *process_flags(char *value, const specs *options);

#endif