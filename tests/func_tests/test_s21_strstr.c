#include "../s21_string_tests.h"

START_TEST(test_s21_strstr_both_empty) {
  const char *haystack = "";
  const char *needle = "";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "example";
  const char *needle = "";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "example";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_at_start) {
  const char *haystack = "hello world";
  const char *needle = "hello";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_at_middle) {
  const char *haystack = "this is a test string";
  const char *needle = "test";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_at_end) {
  const char *haystack = "find the substring";
  const char *needle = "substring";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_full_match) {
  const char *haystack = "match";
  const char *needle = "match";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_no_match) {
  const char *haystack = "abc def";
  const char *needle = "xyz";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_partial_match) {
  const char *haystack = "partial match";
  const char *needle = "partially";
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strstr_long_strings) {
  char haystack[1000];
  char needle[100];
  memset(haystack, 'a', 999);
  memset(needle, 'a', 99);
  haystack[999] = '\0';
  needle[99] = '\0';
  char *res = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *suite = suite_create("s21_strstr");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strstr_both_empty);
  tcase_add_test(tcase, test_s21_strstr_empty_needle);
  tcase_add_test(tcase, test_s21_strstr_empty_haystack);
  tcase_add_test(tcase, test_s21_strstr_at_start);
  tcase_add_test(tcase, test_s21_strstr_at_middle);
  tcase_add_test(tcase, test_s21_strstr_at_end);
  tcase_add_test(tcase, test_s21_strstr_full_match);
  tcase_add_test(tcase, test_s21_strstr_no_match);
  tcase_add_test(tcase, test_s21_strstr_partial_match);
  tcase_add_test(tcase, test_s21_strstr_long_strings);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strstr(void) {
  int number_failed;
  Suite *suite = s21_strstr_suite();
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
