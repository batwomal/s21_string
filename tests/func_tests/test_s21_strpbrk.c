#include "../s21_string_tests.h"

START_TEST(test_s21_strpbrk_both_empty) {
  const char *str1 = "";
  const char *str2 = "";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_first_empty) {
  const char *str1 = "";
  const char *str2 = "abc";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_second_empty) {
  const char *str1 = "abc";
  const char *str2 = "";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_first_match) {
  const char *str1 = "abc";
  const char *str2 = "a";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_last_match) {
  const char *str1 = "abc";
  const char *str2 = "c";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_middle_match) {
  const char *str1 = "abc";
  const char *str2 = "b";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_no_match) {
  const char *str1 = "abc";
  const char *str2 = "xyz";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_multi_match) {
  const char *str1 = "abc";
  const char *str2 = "xyzabc";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_special_chars) {
  const char *str1 = "abc!@#";
  const char *str2 = "!@#";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_overlap) {
  const char *str1 = "123abc456";
  const char *str2 = "789abc";
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_long_strings) {
  char str1[1000];
  char str2[1000];
  memset(str1, 'a', 999);
  memset(str2, 'b', 999);
  str1[999] = '\0';
  str2[999] = '\0';
  str1[500] = 'z';
  str2[700] = 'z';
  char *res = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_null_arguments) {
  const char *str1 = S21_NULL;
  const char *str2 = "abc";
  char *res = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(res, S21_NULL);
}
END_TEST

START_TEST(test_s21_strpbrk_null_arguments2) {
  const char *str1 = "abc";
  const char *str2 = S21_NULL;
  char *res = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(res, S21_NULL);
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *suite = suite_create("s21_strpbrk");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strpbrk_both_empty);
  tcase_add_test(tcase, test_s21_strpbrk_first_empty);
  tcase_add_test(tcase, test_s21_strpbrk_second_empty);
  tcase_add_test(tcase, test_s21_strpbrk_first_match);
  tcase_add_test(tcase, test_s21_strpbrk_last_match);
  tcase_add_test(tcase, test_s21_strpbrk_middle_match);
  tcase_add_test(tcase, test_s21_strpbrk_no_match);
  tcase_add_test(tcase, test_s21_strpbrk_multi_match);
  tcase_add_test(tcase, test_s21_strpbrk_special_chars);
  tcase_add_test(tcase, test_s21_strpbrk_overlap);
  tcase_add_test(tcase, test_s21_strpbrk_long_strings);
  tcase_add_test(tcase, test_s21_strpbrk_null_arguments);
  tcase_add_test(tcase, test_s21_strpbrk_null_arguments2);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strpbrk(void) {
  int number_failed;
  Suite *suite = s21_strpbrk_suite();
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
