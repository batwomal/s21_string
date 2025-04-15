#include "../s21_string_tests.h"

START_TEST(test_s21_strtok_both_empty) {
  char str[] = "";
  const char delim[] = "";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_empty_str) {
  char str[] = "";
  const char delim[] = " ";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_empty_delim) {
  char str[] = "test";
  const char delim[] = "";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_no_delim_in_str) {
  char str[] = "hello";
  const char delim[] = ",";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_single_token_with_delim) {
  char str[] = ",hello,";
  const char delim[] = ",";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  while (res && expected) {
    ck_assert_str_eq(res, expected);
    res = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_multiple_calls) {
  char str[] = "hello,world,this,is,s21";
  const char delim[] = ",";
  char *expected, *result;

  result = s21_strtok(str, delim);
  expected = strtok(str, delim);
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strtok_only_delimiters) {
  char str[] = ";;;;";
  const char delim[] = ";";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_no_delimiters) {
  char str[] = "justastring";
  const char delim[] = ",";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_spaces_as_delimiters) {
  char str[] = "  spaced  tokens  ";
  const char delim[] = " ";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  while (res && expected) {
    ck_assert_str_eq(res, expected);
    res = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_strtok_long_string) {
  char str[1000];
  memset(str, 'a', 999);
  str[999] = '\0';
  const char delim[] = "a";
  char *res = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  while (1) {
    res = s21_strtok(S21_NULL, delim);
    expected = strtok(S21_NULL, delim);

    if (res == S21_NULL && expected == NULL) {
      break;
    }
  }
  ck_assert_ptr_eq(res, expected);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *suite = suite_create("s21_strtok");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_strtok_both_empty);
  tcase_add_test(tcase, test_s21_strtok_empty_str);
  tcase_add_test(tcase, test_s21_strtok_empty_delim);
  tcase_add_test(tcase, test_s21_strtok_no_delim_in_str);
  tcase_add_test(tcase, test_s21_strtok_single_token_with_delim);
  tcase_add_test(tcase, test_s21_strtok_multiple_calls);
  tcase_add_test(tcase, test_s21_strtok_only_delimiters);
  tcase_add_test(tcase, test_s21_strtok_no_delimiters);
  tcase_add_test(tcase, test_s21_strtok_spaces_as_delimiters);
  tcase_add_test(tcase, test_s21_strtok_long_string);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_strtok(void) {
  int number_failed;
  Suite *suite = s21_strtok_suite();
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
