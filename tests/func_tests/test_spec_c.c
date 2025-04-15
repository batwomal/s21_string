#include <check.h>

#include "../../core/io/s21_sprintf.h"
#include "../s21_string_tests.h"

START_TEST(test_spec_c_simple) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};

  int len = spec_c('A', &options, &cursor);

  ck_assert_int_eq(len, 1);
  ck_assert_str_eq(result, "A");
  ck_assert_str_eq(cursor, "");
}
END_TEST

START_TEST(test_spec_c_with_width) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};
  options.width = 5;

  int len = spec_c('B', &options, &cursor);

  ck_assert_int_eq(len, 5);
  ck_assert_str_eq(result, "    B");
  ck_assert_str_eq(cursor, "");
}
END_TEST

START_TEST(test_spec_c_with_width_and_minus) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};
  options.width = 5;
  options.flag[0] = '-';

  int len = spec_c('C', &options, &cursor);

  ck_assert_int_eq(len, 5);
  ck_assert_str_eq(result, "C    ");
  ck_assert_str_eq(cursor, "");
}
END_TEST

START_TEST(test_spec_c_with_width_and_zero) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};
  options.width = 5;
  options.flag[4] = '0';

  int len = spec_c('D', &options, &cursor);

  ck_assert_int_eq(len, 5);
  ck_assert_str_eq(result, "    D");

  ck_assert_str_eq(cursor, "");
}
END_TEST

START_TEST(test_spec_c_with_minus_no_width) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};
  options.flag[0] = '-';

  int len = spec_c('E', &options, &cursor);

  ck_assert_int_eq(len, 1);
  ck_assert_str_eq(result, "E");
  ck_assert_str_eq(cursor, "");
}

END_TEST

START_TEST(test_spec_c_wrong_flags) {
  char result[100] = {0};
  char *cursor = result;
  specs options = {0};
  options.flag[0] = '-';
  options.flag[4] = '0';
  options.length[0] = '1';

  int len = spec_c('E', &options, &cursor);

  ck_assert_int_eq(len, 1);
  ck_assert_str_eq(result, "E");
  ck_assert_str_eq(cursor, "");
}

END_TEST

Suite *spec_c_suite(void) {
  Suite *suite = suite_create("spec_c");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_spec_c_simple);
  tcase_add_test(tcase, test_spec_c_with_width);
  tcase_add_test(tcase, test_spec_c_with_width_and_minus);
  tcase_add_test(tcase, test_spec_c_with_width_and_zero);
  tcase_add_test(tcase, test_spec_c_with_minus_no_width);
  tcase_add_test(tcase, test_spec_c_wrong_flags);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_spec_c() {
  int number_failed;
  Suite *suite = spec_c_suite();
  SRunner *sr = srunner_create(suite);

  system("mkdir -p tests/logs");
  char full_filename[1024];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
