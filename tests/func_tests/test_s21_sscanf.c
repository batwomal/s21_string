/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file
 * "tests/func_tests/tests_check/test_s21_sscanf.c" instead.
 */

#include <check.h>

#include "../s21_string_tests.h"

START_TEST(lol_kek) { s21_sscanf("lol", "kek"); }
END_TEST

START_TEST(null_lol) { s21_sscanf(NULL, "kek"); }
END_TEST

START_TEST(null_kek) { s21_sscanf("lol", NULL); }
END_TEST

START_TEST(null_lol_null_kek) { s21_sscanf(NULL, NULL); }
END_TEST

int test_s21_sscanf(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  /* User-specified pre-run code */
  system("mkdir -p tests/logs");
  char full_filename[BUF_SIZE];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, lol_kek);
  tcase_add_test(tc1_1, null_lol);
  tcase_add_test(tc1_1, null_kek);
  tcase_add_test(tc1_1, null_lol_null_kek);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  /* User-specified post-run code */
  return nf;
}
