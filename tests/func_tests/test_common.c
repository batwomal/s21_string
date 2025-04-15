#include "../../s21_string.h"
#include "../s21_string_tests.h"

START_TEST(test_s21_error) { s21_error("test_program", "Test error message"); }
END_TEST

START_TEST(test_s21_calloc_success) {
  s21_size_t size = 100;
  void *ptr = s21_calloc(size);
  ck_assert_ptr_ne(ptr, S21_NULL);
  free(ptr);
}
END_TEST

START_TEST(test_s21_calloc_failure) {
  s21_size_t size = SIZE_MAX;
  void *ptr = s21_calloc(size);
  ck_assert_ptr_eq(ptr, S21_NULL);
}
END_TEST

START_TEST(test_s21_realloc_success) {
  s21_size_t size = 50;
  void *ptr = s21_calloc(size);
  ck_assert_ptr_ne(ptr, S21_NULL);

  s21_size_t new_size = 100;
  void *new_ptr = s21_realloc(ptr, new_size);
  ck_assert_ptr_ne(new_ptr, S21_NULL);
  free(new_ptr);
}
END_TEST

START_TEST(test_s21_strdup_success) {
  const char *str = "Hello, world!";
  char *copy = s21_strdup(str);
  ck_assert_ptr_ne(copy, S21_NULL);
  ck_assert_str_eq(copy, str);
  free(copy);
}
END_TEST

START_TEST(test_s21_strdup_null) {
  char *copy = s21_strdup(S21_NULL);
  ck_assert_ptr_eq(copy, S21_NULL);
}
END_TEST

START_TEST(test_s21_strdup_empty_string) {
  const char *str = "";
  char *copy = s21_strdup(str);
  ck_assert_ptr_ne(copy, S21_NULL);
  ck_assert_str_eq(copy, str);
  free(copy);
}
END_TEST

START_TEST(test_s21_realloc_failure2) {
  void *mem = s21_calloc(100);
  ck_assert_ptr_ne(mem, S21_NULL);

  void *new_mem = s21_realloc(mem, SIZE_MAX);
  ck_assert_ptr_eq(new_mem, S21_NULL);
}
END_TEST

START_TEST(test_s21_strdup_failure) {
  const char *str = "Hello, world!";

  void *copy = s21_strdup(str);
  ck_assert_ptr_ne(copy, S21_NULL);
  free(copy);

  void *copy_failed = s21_strdup(S21_NULL);
  ck_assert_ptr_eq(copy_failed, S21_NULL);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_error);
  tcase_add_test(tc_core, test_s21_calloc_success);
  tcase_add_test(tc_core, test_s21_calloc_failure);
  tcase_add_test(tc_core, test_s21_realloc_success);
  tcase_add_test(tc_core, test_s21_strdup_success);
  tcase_add_test(tc_core, test_s21_strdup_null);
  tcase_add_test(tc_core, test_s21_strdup_empty_string);
  tcase_add_test(tc_core, test_s21_realloc_failure2);
  tcase_add_test(tc_core, test_s21_strdup_failure);

  suite_add_tcase(s, tc_core);
  return s;
}

int test_common(void) {
  int number_failed;
  Suite *s = s21_string_suite();
  SRunner *sr = srunner_create(s);

  system("mkdir -p tests/logs");
  char full_filename[1024];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
