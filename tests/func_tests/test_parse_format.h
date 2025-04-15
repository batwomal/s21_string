#ifndef TEST_PARSE_FORMAT_H
#define TEST_PARSE_FORMAT_H

#include "../../../src/core/io/s21_sprintf.h"
#include "../s21_string_tests.h"

typedef struct {
  const char *format_str;
  int variable_width;
  int variable_precision;
} input_parse_format;

typedef struct {
  const char *expected_output_str;
  specs expected_output;
} output_parse_format;

typedef struct {
  input_parse_format input;
  output_parse_format output;
} test_parse_format_data;

#define PARSE_TEST_CASES                                                       \
  {                                                                            \
    {{"%s", 0, 0}, {"", {'s', -2, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},            \
        {{"%cZZZZ", 0, 0},                                                     \
         {"ZZZZ", {'c', -2, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},                  \
        {{"%d", 0, 0}, {"", {'d', -2, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},        \
        {{"%.f", 0, 0}, {"", {'f', 0, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},        \
        {{"%.5f", 0, 0}, {"", {'f', 5, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},       \
        {{"%5.f", 0, 0}, {"", {'f', 0, 5, {0, 0, 0, 0, 0}, {0, 0, 0}}}},       \
        {{"%5.5f", 0, 0}, {"", {'f', 5, 5, {0, 0, 0, 0, 0}, {0, 0, 0}}}},      \
        {{"%%", 0, 0}, {"", {'%', -2, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},        \
        {{"%*d", 10, 0}, {"", {'d', -2, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},     \
        {{"%*.*d", 10, 10}, {"", {'d', 10, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},  \
        {{"%*.*d", 10, 0}, {"", {'d', -1, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},   \
        {{"%+-# 0s", 0, 0},                                                    \
         {"", {'s', -2, 0, {'-', '+', ' ', '#', '0'}, {0, 0, 0}}}},            \
        {{"% -+s", 0, 0},                                                      \
         {"", {'s', -2, 0, {'-', '+', ' ', 0, 0}, {0, 0, 0}}}},                \
        {{"%z", 0, 0}, {"", {0, 6, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},           \
        {{"%lld", 0, 0}, {"", {'d', -2, 0, {0, 0, 0, 0, 0}, {0, 2, 0}}}},      \
        {{"%Lf", 0, 0}, {"", {'f', 6, 0, {0, 0, 0, 0, 0}, {0, 0, 1}}}},        \
        {{"%hd", 0, 0}, {"", {'d', -2, 0, {0, 0, 0, 0, 0}, {1, 0, 0}}}},       \
        {{"%#5x", 0, 0}, {"", {'x', -2, 5, {0, 0, 0, '#', 0}, {0, 0, 0}}}},    \
        {{"%-10.4d", 0, 0}, {"", {'d', 4, 10, {'-', 0, 0, 0, 0}, {0, 0, 0}}}}, \
        {{"%010d", 0, 0}, {"", {'d', -2, 10, {0, 0, 0, 0, '0'}, {0, 0, 0}}}},  \
        {{"%10.5lf", 0, 0}, {"", {'f', 5, 10, {0, 0, 0, 0, 0}, {0, 1, 0}}}},   \
        {{"%+-10.3f", 0, 0},                                                   \
         {"", {'f', 3, 10, {'-', '+', 0, 0, 0}, {0, 0, 0}}}},                  \
        {{"%+ 8.2f", 0, 0},                                                    \
         {"", {'f', 2, 8, {0, '+', ' ', 0, 0}, {0, 0, 0}}}},                   \
        {{"%-20d", 0, 0}, {"", {'d', -2, 20, {'-', 0, 0, 0, 0}, {0, 0, 0}}}},  \
        {{"%2.3x", 0, 0}, {"", {'x', 3, 2, {0, 0, 0, 0, 0}, {0, 0, 0}}}},      \
        {{"%0-5d", 0, 0}, {"", {'d', -2, 5, {'-', 0, 0, 0, '0'}, {0, 0, 0}}}}, \
        {{"%5.2f", 0, 0}, {"", {'f', 2, 5, {0, 0, 0, 0, 0}, {0, 0, 0}}}},      \
        {{"%0+10d", 0, 0},                                                     \
         {"", {'d', -2, 10, {0, '+', 0, 0, '0'}, {0, 0, 0}}}},                 \
        {{"%*.*s", 5, 3}, {"", {'s', 3, 5, {0, 0, 0, 0, 0}, {0, 0, 0}}}},      \
        {{"%10s", 0, 0}, {"", {'s', -2, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},     \
        {{"%-10.3f", 0, 0}, {"", {'f', 3, 10, {'-', 0, 0, 0, 0}, {0, 0, 0}}}}, \
        {{"%10d", 0, 0}, {"", {'d', -2, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},     \
        {{"%1.2f", 0, 0}, {"", {'f', 2, 1, {0, 0, 0, 0, 0}, {0, 0, 0}}}},      \
        {{"%dleftovers", 0, 0},                                                \
         {"leftovers", {'d', -2, 0, {0, 0, 0, 0, 0}, {0, 0, 0}}}},             \
        {{"%*.*dleftovers", 10, 5},                                            \
         {"leftovers", {'d', 5, 10, {0, 0, 0, 0, 0}, {0, 0, 0}}}},             \
    {                                                                          \
      {"%*.*dleftovers", 10, 5}, {                                             \
        "leftovers", {                                                         \
          'd', 5, 10, {0, 0, 0, 0, 0}, { 0, 0, 0 }                             \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

#endif