#include "../s21_string_tests.h"

START_TEST(test_s21_insert_at_start) {
  const char *src = "world";
  const char *insert = "hello ";
  char *expected = "hello world";
  s21_size_t index = 0;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_at_end) {
  const char *src = "hello";
  const char *insert = " world";
  char *expected = "hello world";
  s21_size_t index = 5;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_in_middle) {
  const char *src = "helld";
  const char *insert = "lo wor";
  char *expected = "hello world";
  s21_size_t index = 3;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_insert) {
  const char *src = "hello world";
  const char *insert = "";
  char *expected = "hello world";
  s21_size_t index = 5;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_src) {
  const char *src = "";
  const char *insert = "hello world";
  char *expected = "hello world";
  s21_size_t index = 0;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_index_out_of_bounds) {
  const char *src = "hello";
  const char *insert = " world";
  char *result = s21_insert(src, insert, 10);

  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_insert_empty_both) {
  const char *src = "";
  const char *insert = "";
  char *expected = "";
  s21_size_t index = 0;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_large_insert) {
  const char *src = "hello";
  char insert[1000];
  memset(insert, 'x', 999);
  insert[999] = '\0';

  char expected[1005];
  strncpy(expected, src, 5);
  expected[5] = '\0';
  strcat(expected, insert);
  strcat(expected, src + 5);

  s21_size_t index = 5;
  char *result = s21_insert(src, insert, index);

  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_src_null) {
  const char *src = S21_NULL;
  const char *insert = "hello";
  char *result = s21_insert(src, insert, 0);

  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_insert_str_null) {
  const char *src = "hello";
  const char *insert = S21_NULL;
  char *result = s21_insert(src, insert, 2);

  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_insert_str__and_src_null) {
  char *result = s21_insert(S21_NULL, S21_NULL, 0);

  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_insert_index_equal_to_length) {
  const char *src = "hello";
  const char *insert = " world";
  char *expected = "hello world";
  s21_size_t index = 5;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_single_char) {
  const char *src = "h";
  const char *insert = "ello";
  char *expected = "hello";
  s21_size_t index = 1;

  char *result = s21_insert(src, insert, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *suite = suite_create("s21_insert");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_insert_at_start);
  tcase_add_test(tcase, test_s21_insert_at_end);
  tcase_add_test(tcase, test_s21_insert_in_middle);
  tcase_add_test(tcase, test_s21_insert_empty_insert);
  tcase_add_test(tcase, test_s21_insert_empty_src);
  tcase_add_test(tcase, test_s21_insert_index_out_of_bounds);
  tcase_add_test(tcase, test_s21_insert_empty_both);
  tcase_add_test(tcase, test_s21_insert_large_insert);
  tcase_add_test(tcase, test_s21_insert_src_null);
  tcase_add_test(tcase, test_s21_insert_str_null);
  tcase_add_test(tcase, test_s21_insert_str__and_src_null);
  tcase_add_test(tcase, test_s21_insert_index_equal_to_length);
  tcase_add_test(tcase, test_s21_insert_single_char);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_insert(void) {
  int number_failed;
  Suite *suite = s21_insert_suite();
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
