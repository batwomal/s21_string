#include "../s21_string_tests.h"

START_TEST(test_s21_strncpy_basic_copy) {
  char dest[100] = {0};
  const char *src = "Hello, world!";
  s21_size_t n = 5;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncpy_partial_copy) {
  char dest[100] = {0};
  const char *src = "Hello";
  s21_size_t n = 10;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_mem_eq(res, expected, n);
}
END_TEST

START_TEST(test_s21_strncpy_full_copy) {
  char dest[100] = {0};
  const char *src = "Hello";
  s21_size_t n = 5;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncpy_empty_src) {
  char dest[100] = {0};
  const char *src = "";
  s21_size_t n = 5;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_mem_eq(res, expected, n);
}
END_TEST

START_TEST(test_s21_strncpy_zero_n) {
  char dest[100] = {0};
  const char *src = "Hello, world!";
  s21_size_t n = 0;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncpy_large_n) {
  char dest[100] = {0};
  const char *src = "Test";
  s21_size_t n = 50;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_mem_eq(res, expected, n);
}
END_TEST

START_TEST(test_s21_strncpy_null_termination) {
  char dest[100] = {0};
  const char *src = "Test";
  s21_size_t n = 2;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_mem_eq(res, expected, 3);
}
END_TEST

START_TEST(test_s21_strncpy_overwrite) {
  char dest[100] = "Old data here";
  const char *src = "New";
  s21_size_t n = 10;
  char *res = s21_strncpy(dest, src, n);
  char *expected = strncpy(dest, src, n);
  ck_assert_mem_eq(res, expected, n);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *suite = suite_create("s21_strncpy");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strncpy_basic_copy);
  tcase_add_test(tcase, test_s21_strncpy_partial_copy);
  tcase_add_test(tcase, test_s21_strncpy_full_copy);
  tcase_add_test(tcase, test_s21_strncpy_empty_src);
  tcase_add_test(tcase, test_s21_strncpy_zero_n);
  tcase_add_test(tcase, test_s21_strncpy_large_n);
  tcase_add_test(tcase, test_s21_strncpy_null_termination);
  tcase_add_test(tcase, test_s21_strncpy_overwrite);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strncpy() {
  int number_failed;
  Suite *suite = s21_strncpy_suite();
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
