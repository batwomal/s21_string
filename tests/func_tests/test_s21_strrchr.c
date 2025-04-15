#include "../s21_string_tests.h"

START_TEST(test_s21_strrchr_empty_string) {
  const char *str = "";
  int ch = 'a';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_char_not_found) {
  const char *str = "Hello, world!";
  int ch = 'z';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_char_in_middle) {
  const char *str = "abcdeabc";
  int ch = 'c';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_char_at_end) {
  const char *str = "abcde";
  int ch = 'e';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_char_at_start) {
  const char *str = "abcde";
  int ch = 'a';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_repeated_char) {
  const char *str = "abcabcabc";
  int ch = 'a';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_null_char) {
  const char *str = "Hello, world!";
  int ch = '\0';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strrchr_long_string) {
  char str[1000];
  memset(str, 'a', 999);
  str[999] = '\0';
  str[500] = 'z';
  int ch = 'z';
  char *res = s21_strrchr(str, ch);
  char *expected = strrchr(str, ch);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *suite = suite_create("s21_strrchr");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strrchr_empty_string);
  tcase_add_test(tcase, test_s21_strrchr_char_not_found);
  tcase_add_test(tcase, test_s21_strrchr_char_in_middle);
  tcase_add_test(tcase, test_s21_strrchr_char_at_end);
  tcase_add_test(tcase, test_s21_strrchr_char_at_start);
  tcase_add_test(tcase, test_s21_strrchr_repeated_char);
  tcase_add_test(tcase, test_s21_strrchr_null_char);
  tcase_add_test(tcase, test_s21_strrchr_long_string);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strrchr(void) {
  int number_failed;
  Suite *suite = s21_strrchr_suite();
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
