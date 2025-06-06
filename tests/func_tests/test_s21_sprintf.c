/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file
 * "tests/func_tests/tests_check/test_s21_sprintf.c" instead.
 */

#include "test_s21_sprintf.h"

#include <check.h>

#include "../s21_string_tests.h"

START_TEST(no_spec) {
  char *inputs_no_spec[] = INPUT_NO_SPEC;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int s21_len = s21_sprintf(s21_out, inputs_no_spec[_i]);
  int orig_len = -1;
  if (inputs_no_spec[_i]) orig_len = sprintf(orig_out, inputs_no_spec[_i], 0);
  int result = s21_len == orig_len && strcmp(s21_out, orig_out) == 0;
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {%s}]\n",
                orig_len, s21_len, orig_out, s21_out, inputs_no_spec[_i]);
}
END_TEST

START_TEST(spec_c) {
  input_spec_c input[] = INPUT_SPEC_C;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].c);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].c);
  int result = len_s21 == len_orig && strcmp(s21_out, orig_out) == 0;
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {%s} , %c]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].c);
}
END_TEST

START_TEST(spec_percent) {
  char *input[] = INPUT_SPEC_PERCENT;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i], 0);
  int len_orig = sprintf(orig_out, input[_i], 0);
  int result = len_s21 == len_orig && strcmp(s21_out, orig_out) == 0;
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {%s}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i]);
}
END_TEST

START_TEST(spec_s) {
  input_spec_s input[] = INPUT_SPEC_S;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].str);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].str);
  int result = len_s21 == len_orig && strcmp(s21_out, orig_out) == 0;
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {%s} , {%s}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].str);
}
END_TEST

START_TEST(spec_d) {
  input_spec_ints input[] = INPUT_SPEC_D;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = len_s21 == len_orig && strcmp(s21_out, orig_out) == 0;
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %lld}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_u) {
  input_spec_ints input[] = INPUT_SPEC_U;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %llu}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_x) {
  input_spec_ints input[] = INPUT_SPEC_X;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %llx}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_x_cap) {
  input_spec_ints input[] = INPUT_SPEC_X_CAP;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %llX}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_o) {
  input_spec_ints input[] = INPUT_SPEC_O;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %llo}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_i) {
  input_spec_ints input[] = INPUT_SPEC_I;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %lli}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_p) {
  input_spec_c input[] = INPUT_SPEC_P;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, &input[_i].c);
  int len_orig = sprintf(orig_out, input[_i].input, &input[_i].c);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %p}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                &input[_i].c);
}
END_TEST

START_TEST(spec_p_null) {
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, "aaaa%pZZZZ", NULL);
  int len_orig = sprintf(orig_out, "aaaa%pZZZZ", NULL);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: %s]\n[s21 str: "
                "%s]\n[input: %p]\n",
                len_orig, len_s21, orig_out, s21_out, NULL);
}
END_TEST

START_TEST(spec_f) {
  input_spec_floats input[] = INPUT_SPEC_F;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %Lf}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_e) {
  input_spec_floats input[] = INPUT_SPEC_E;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %Le}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_e_caps) {
  input_spec_floats input[] = INPUT_SPEC_E_CAPS;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %LE}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_g) {
  input_spec_floats input[] = INPUT_SPEC_G;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %Lg}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_g_caps) {
  input_spec_floats input[] = INPUT_SPEC_G_CAPS;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %LG}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_g_caps_double) {
  input_spec_doubles input[] = INPUT_SPEC_G_CAPS_DOUBLE;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %G}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_e_caps_double) {
  input_spec_doubles input[] = INPUT_SPEC_E_CAPS_DOUBLE;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %E}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

START_TEST(spec_f_caps_double) {
  input_spec_doubles input[] = INPUT_SPEC_F_CAPS_DOUBLE;
  char s21_out[BUF_SIZE] = {0};
  char orig_out[BUF_SIZE] = {0};
  int len_s21 = s21_sprintf(s21_out, input[_i].input, input[_i].num);
  int len_orig = sprintf(orig_out, input[_i].input, input[_i].num);
  int result = (len_s21 == len_orig) && (strcmp(s21_out, orig_out) == 0);
  ck_assert_msg(result,
                "\n[orig len: %d]\n[s21 len: %d]\n[orig str: {%s}]\n[s21 str: "
                "{%s}]\n[input: {{%s} , %f}]\n",
                len_orig, len_s21, orig_out, s21_out, input[_i].input,
                input[_i].num);
}
END_TEST

int test_s21_sprintf(void) {
  Suite *s1 = suite_create("s21_sprintf");
  TCase *tc1_1 = tcase_create("s21_sprintf");
  SRunner *sr = srunner_create(s1);
  int nf;

  /* User-specified pre-run code */
  system("mkdir -p tests/logs");
  char full_filename[BUF_SIZE];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  suite_add_tcase(s1, tc1_1);
  tcase_add_loop_test(tc1_1, no_spec, 0, 6);
  tcase_add_loop_test(tc1_1, spec_c, 0, 10);
  tcase_add_loop_test(tc1_1, spec_percent, 0, 4);
  tcase_add_loop_test(tc1_1, spec_s, 0, 20);
  tcase_add_loop_test(tc1_1, spec_d, 0, 46);
  tcase_add_loop_test(tc1_1, spec_u, 0, 46);
  tcase_add_loop_test(tc1_1, spec_x, 0, 46);
  tcase_add_loop_test(tc1_1, spec_x_cap, 0, 46);
  tcase_add_loop_test(tc1_1, spec_o, 0, 46);
  tcase_add_loop_test(tc1_1, spec_i, 0, 46);
  tcase_add_loop_test(tc1_1, spec_p, 0, 10);
  tcase_add_test(tc1_1, spec_p_null);
  tcase_add_loop_test(tc1_1, spec_f, 0, 60);
  tcase_add_loop_test(tc1_1, spec_e, 0, 60);
  tcase_add_loop_test(tc1_1, spec_e_caps, 0, 60);
  tcase_add_loop_test(tc1_1, spec_g, 0, 60);
  tcase_add_loop_test(tc1_1, spec_g_caps, 0, 60);
  tcase_add_loop_test(tc1_1, spec_g_caps_double, 0, 60);
  tcase_add_loop_test(tc1_1, spec_e_caps_double, 0, 60);
  tcase_add_loop_test(tc1_1, spec_f_caps_double, 0, 60);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  /* User-specified post-run code */
  return nf;
}
