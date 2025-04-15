#include "../s21_string_tests.h"

START_TEST(test_s21_to_upper_lowercase_to_uppercase) {
  const char src[] = "hello world";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "HELLO WORLD");
}
END_TEST

START_TEST(test_s21_to_upper_uppercase) {
  const char src[] = "HELLO WORLD";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "HELLO WORLD");
}
END_TEST

START_TEST(test_s21_to_upper_mixed) {
  const char src[] = "Hello 123! World";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "HELLO 123! WORLD");
}
END_TEST

START_TEST(test_s21_to_upper_non_alpha) {
  const char src[] = "123456 !@#$%";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "123456 !@#$%");
}
END_TEST

START_TEST(test_s21_to_upper_empty_string) {
  const char src[] = "";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(test_s21_to_upper_null_pointer) {
  const char *src = NULL;
  char *result = s21_to_upper(src);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_to_upper_char_a) {
  const char src[] = "a";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "A");
}
END_TEST

START_TEST(test_s21_to_upper_char_z) {
  const char src[] = "z";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "Z");
}
END_TEST

START_TEST(test_s21_to_upper_96symbol) {
  const char src[] = "`";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "`");
}
END_TEST

START_TEST(test_s21_to_upper_123symbol) {
  const char src[] = "{";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, "{");
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *suite = suite_create("s21_to_upper");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_to_upper_lowercase_to_uppercase);
  tcase_add_test(tcase, test_s21_to_upper_uppercase);
  tcase_add_test(tcase, test_s21_to_upper_mixed);
  tcase_add_test(tcase, test_s21_to_upper_non_alpha);
  tcase_add_test(tcase, test_s21_to_upper_empty_string);
  tcase_add_test(tcase, test_s21_to_upper_null_pointer);
  tcase_add_test(tcase, test_s21_to_upper_char_a);
  tcase_add_test(tcase, test_s21_to_upper_char_z);
  tcase_add_test(tcase, test_s21_to_upper_96symbol);
  tcase_add_test(tcase, test_s21_to_upper_123symbol);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_to_upper(void) {
  int number_failed;
  Suite *suite = s21_to_upper_suite();
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
