#ifndef TEST_S21_LFTOA_H_
#define TEST_S21_LFTOA_H_

typedef struct {
  float num;
  int precision;
} input_f_s21_lftoa;

typedef struct {
  double num;
  int precision;
} input_d_s21_lftoa;

typedef struct {
  long double num;
  int precision;
} input_ld_s21_lftoa;

#define INPUT_FLOAT_DATA                                                      \
  {                                                                           \
    {0.0, 1}, {-0.0, 1}, {FLT_MIN, FLT_DIG}, {FLT_MAX, 6}, {1232.123, 6},     \
        {-1232.123, 6}, {0.9, 6}, {0.9, 2}, {DBL_MIN, DBL_DIG}, {DBL_MAX, 6}, \
        {-LDBL_MAX, 6}, {-1232.123, 6}, {0.9, 6}, {0.9, 2},                   \
        {LDBL_MIN, LDBL_DIG}, {LDBL_MAX, 6}, {NAN, 6}, {FLT_MIN, 600},        \
        {0.9, 6}, {                                                           \
      0.9, 2                                                                  \
    }                                                                         \
  }

#define INPUT_DOUBLE_DATA                                                     \
  {                                                                           \
    {0.0, 1}, {-0.0, 1}, {FLT_MIN, FLT_DIG}, {FLT_MAX, 6}, {1232.123, 6},     \
        {-1232.123, 6}, {0.9, 6}, {0.9, 2}, {DBL_MIN, DBL_DIG}, {DBL_MAX, 6}, \
        {-LDBL_MAX, 6}, {-1232.123, 6}, {0.9, 6}, {0.9, 2},                   \
        {LDBL_MIN, LDBL_DIG}, {LDBL_MAX, 6}, {NAN, 6}, {DBL_MIN, 600},        \
        {0.9, 6}, {                                                           \
      0.9, 2                                                                  \
    }                                                                         \
  }

#define INPUT_LONG_DOUBLE_DATA                                                \
  {                                                                           \
    {0.0, 1}, {-0.0, 1}, {FLT_MIN, FLT_DIG}, {FLT_MAX, 6}, {1232.123, 6},     \
        {-1232.123, 6}, {0.9, 6}, {0.9, 2}, {DBL_MIN, DBL_DIG}, {DBL_MAX, 6}, \
        {-DBL_MAX, 6}, {999.99999999999L, 15}, {0.9, 6}, {0.9, 2},            \
        {LDBL_MIN, LDBL_DIG}, {DBL_MAX, 6}, {NAN, 6}, {LDBL_MIN, 4944},       \
        {0.9, 6}, {                                                           \
      0.9, 2                                                                  \
    }                                                                         \
  }

#endif  // TEST_S21_LFTOA_H_