#include "../s21_string_tests.h"

START_TEST(test_s21_strerror_zero) {
  int errnum = 0;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_valid_error) {
  int errnum = 1;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_negative_error) {
  int errnum = -1;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_large_error) {
  int errnum = 9999;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_mid_range_error) {
  int errnum = 5;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_int_max) {
  int errnum = INT_MAX;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strerror_int_min) {
  int errnum = INT_MIN;
  char *res = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *tcase = tcase_create("s21_strerror");

  tcase_add_test(tcase, test_s21_strerror_zero);
  tcase_add_test(tcase, test_s21_strerror_valid_error);
  tcase_add_test(tcase, test_s21_strerror_negative_error);
  tcase_add_test(tcase, test_s21_strerror_large_error);
  tcase_add_test(tcase, test_s21_strerror_mid_range_error);
  tcase_add_test(tcase, test_s21_strerror_int_max);
  tcase_add_test(tcase, test_s21_strerror_int_min);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strerror(void) {
  int number_failed;
  Suite *suite = s21_strerror_suite();
  SRunner *sr = srunner_create(suite);

  system("mkdir -p tests/logs");
  char full_filename[1024];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);

  srunner_set_log(sr, full_filename);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
