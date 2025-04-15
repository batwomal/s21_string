#include "../s21_string_tests.h"

START_TEST(test_s21_strncmp_both_empty) {
  const char *str1 = "";
  const char *str2 = "";
  s21_size_t n = 5;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_identical_strings_n_less) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  s21_size_t n = 3;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_identical_strings_n_more) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  s21_size_t n = 10;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_first_less) {
  const char *str1 = "abc";
  const char *str2 = "abd";
  s21_size_t n = 3;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_second_less) {
  const char *str1 = "abd";
  const char *str2 = "abc";
  s21_size_t n = 3;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_n_zero) {
  const char *str1 = "abc";
  const char *str2 = "def";
  s21_size_t n = 0;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_one_empty) {
  const char *str1 = "";
  const char *str2 = "hello";
  s21_size_t n = 5;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_diff_strings_n_less) {
  const char *str1 = "abcdef";
  const char *str2 = "abcxyz";
  s21_size_t n = 3;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_diff_strings_n_more) {
  const char *str1 = "abcdef";
  const char *str2 = "abcxyz";
  s21_size_t n = 6;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_diff_length_short_limit) {
  const char *str1 = "hello";
  const char *str2 = "hello, world";
  s21_size_t n = 5;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strncmp_long_strings) {
  char str1[1000], str2[1000];
  memset(str1, 'a', 999);
  memset(str2, 'a', 999);
  str1[999] = '\0';
  str2[999] = '\0';
  s21_size_t n = 1000;
  int res = s21_strncmp(str1, str2, n);
  int expected = strncmp(str1, str2, n);
  ck_assert_int_eq(res, expected);
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *suite = suite_create("s21_strncmp");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strncmp_both_empty);
  tcase_add_test(tcase, test_s21_strncmp_identical_strings_n_less);
  tcase_add_test(tcase, test_s21_strncmp_identical_strings_n_more);
  tcase_add_test(tcase, test_s21_strncmp_first_less);
  tcase_add_test(tcase, test_s21_strncmp_second_less);
  tcase_add_test(tcase, test_s21_strncmp_n_zero);
  tcase_add_test(tcase, test_s21_strncmp_one_empty);
  tcase_add_test(tcase, test_s21_strncmp_diff_strings_n_less);
  tcase_add_test(tcase, test_s21_strncmp_diff_strings_n_more);
  tcase_add_test(tcase, test_s21_strncmp_diff_length_short_limit);
  tcase_add_test(tcase, test_s21_strncmp_long_strings);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strncmp(void) {
  int number_failed;
  Suite *suite = s21_strncmp_suite();
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
