#include <time.h>

#include "../s21_string_tests.h"

START_TEST(test_s21_trim_both_empty) {
  const char *src = "";
  const char *trim_chars = "";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_src) {
  const char *src = "";
  const char *trim_chars = "abc";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_trim_chars) {
  const char *src = "   abc   ";
  const char *trim_chars = "";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "   abc   ");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_both_sides) {
  const char *src = "   abc   ";
  const char *trim_chars = " ";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_left_side) {
  const char *src = "   abc";
  const char *trim_chars = " ";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_right_side) {
  const char *src = "abc   ";
  const char *trim_chars = " ";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_multiple_chars) {
  const char *src = "---abc---";
  const char *trim_chars = "-";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_no_match_trim_chars) {
  const char *src = "abc";
  const char *trim_chars = "xyz";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_full_trim) {
  const char *src = "aaaaa";
  const char *trim_chars = "a";
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_long_string) {
  char src[1000];
  char trim_chars[10];
  memset(src, 'a', 999);
  src[999] = '\0';
  memset(trim_chars, 'a', 9);
  trim_chars[9] = '\0';
  void *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_first_arg_null) {
  const char *trim_chars = "abc";
  void *result = s21_trim(NULL, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_second_arg_null) {
  const char *src = "abc";
  void *result = s21_trim(src, NULL);
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_both_null) {
  void *result = s21_trim(NULL, NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *suite = suite_create("s21_trim");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_trim_both_empty);
  tcase_add_test(tcase, test_s21_trim_empty_src);
  tcase_add_test(tcase, test_s21_trim_empty_trim_chars);
  tcase_add_test(tcase, test_s21_trim_both_sides);
  tcase_add_test(tcase, test_s21_trim_left_side);
  tcase_add_test(tcase, test_s21_trim_right_side);
  tcase_add_test(tcase, test_s21_trim_multiple_chars);
  tcase_add_test(tcase, test_s21_trim_no_match_trim_chars);
  tcase_add_test(tcase, test_s21_trim_full_trim);
  tcase_add_test(tcase, test_s21_trim_long_string);
  tcase_add_test(tcase, test_s21_trim_first_arg_null);
  tcase_add_test(tcase, test_s21_trim_second_arg_null);
  tcase_add_test(tcase, test_s21_trim_both_null);
  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_trim(void) {
  int number_failed;
  Suite *suite = s21_trim_suite();
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
