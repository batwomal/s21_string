#include "../s21_string_tests.h"

START_TEST(test_s21_strncat_basic_concat) {
  char dest[100] = "Hello, ";
  const char *src = "world!";
  s21_size_t n = 6;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  char dest[100] = "Hello, ";
  const char *src = "";
  s21_size_t n = 5;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_zero_n) {
  char dest[100] = "Hello, ";
  const char *src = "world!";
  s21_size_t n = 0;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char dest[100] = "";
  const char *src = "world!";
  s21_size_t n = 6;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_large_n) {
  char dest[100] = "Hello, ";
  const char *src = "world!";
  s21_size_t n = 50;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_no_null_overwrite) {
  char dest[100] = "Hello";
  dest[6] = 'X';
  const char *src = "world!";
  s21_size_t n = 3;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_mem_eq(res, expected, strlen(expected) + 1);
}
END_TEST

START_TEST(test_s21_strncat_long_strings) {
  char dest[1000] = "Initial text ";
  char src[1000];
  memset(src, 'a', 999);
  src[999] = '\0';
  s21_size_t n = 900;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncat_special_chars) {
  char dest[100] = "Special: ";
  const char *src = "@#$%^&*()";
  s21_size_t n = 10;
  char *res = s21_strncat(dest, src, n);
  char *expected = strncat(dest, src, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *suite = suite_create("s21_strncat");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strncat_basic_concat);
  tcase_add_test(tcase, test_s21_strncat_empty_src);
  tcase_add_test(tcase, test_s21_strncat_zero_n);
  tcase_add_test(tcase, test_s21_strncat_empty_dest);
  tcase_add_test(tcase, test_s21_strncat_large_n);
  tcase_add_test(tcase, test_s21_strncat_no_null_overwrite);
  tcase_add_test(tcase, test_s21_strncat_long_strings);
  tcase_add_test(tcase, test_s21_strncat_special_chars);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strncat(void) {
  int number_failed;
  Suite *suite = s21_strncat_suite();
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
