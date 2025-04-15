#include "../s21_string_tests.h"

START_TEST(test_s21_to_lower_uppercase_to_lowercase) {
  const char src[] = "HELLO WORLD";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, "hello world");
}
END_TEST

START_TEST(test_s21_to_lower_lowercase) {
  const char src[] = "hello world";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, "hello world");
}
END_TEST

START_TEST(test_s21_to_lower_mixed) {
  const char src[] = "Hello 123! World";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, "hello 123! world");
}
END_TEST

START_TEST(test_s21_to_lower_non_alpha) {
  const char src[] = "123456 !@#$%";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, "123456 !@#$%");
}
END_TEST

START_TEST(test_s21_to_lower_empty_string) {
  const char src[] = "";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(test_s21_to_lower_null_pointer) {
  const char *src = NULL;
  char *result = s21_to_lower(src);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_to_lower_suite(void) {
  Suite *suite = suite_create("s21_to_lower");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_to_lower_uppercase_to_lowercase);
  tcase_add_test(tcase, test_s21_to_lower_lowercase);
  tcase_add_test(tcase, test_s21_to_lower_mixed);
  tcase_add_test(tcase, test_s21_to_lower_non_alpha);
  tcase_add_test(tcase, test_s21_to_lower_empty_string);
  tcase_add_test(tcase, test_s21_to_lower_null_pointer);

  suite_add_tcase(suite, tcase);
  return suite;
}
int test_s21_to_lower(void) {
  int number_failed;
  Suite *suite = s21_to_lower_suite();
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
