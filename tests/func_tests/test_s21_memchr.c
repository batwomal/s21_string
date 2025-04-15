#include "../s21_string_tests.h"

START_TEST(test_s21_memchr_empty) {
  char *s = "";
  void *res = s21_memchr(s, 'a', 0);
  void *expected = memchr(s, 'a', 0);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memchr_not_found) {
  char s[] = "Hello, World!";
  void *res = s21_memchr(s, 'z', strlen(s));
  void *expected = memchr(s, 'z', strlen(s));
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memchr_middle) {
  char s[] = "Hello, World!";
  void *res = s21_memchr(s, 'o', strlen(s));
  void *expected = memchr(s, 'o', strlen(s));
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memchr_start) {
  char s[] = "Hello, World!";
  void *res = s21_memchr(s, 'H', strlen(s));
  void *expected = memchr(s, 'H', strlen(s));
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memchr_end) {
  char s[] = "Hello, World!";
  void *res = s21_memchr(s, '!', strlen(s));
  void *expected = memchr(s, '!', strlen(s));
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memchr_various_chars) {
  char s[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; i++) {
    void *res = s21_memchr(s, i, 10);
    void *expected = memchr(s, i, 10);
    ck_assert_ptr_eq(res, expected);
  }
}
END_TEST

START_TEST(test_s21_memchr_large_data) {
  char *s = malloc(1000000);
  memset(s, 'a', 1000000);
  s[500000] = 'b';
  void *res = s21_memchr(s, 'b', 1000000);
  void *expected = memchr(s, 'b', 1000000);
  ck_assert_ptr_eq(res, expected);
  free(s);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_memchr_empty);
  tcase_add_test(tcase, test_s21_memchr_not_found);
  tcase_add_test(tcase, test_s21_memchr_middle);
  tcase_add_test(tcase, test_s21_memchr_start);
  tcase_add_test(tcase, test_s21_memchr_end);
  tcase_add_test(tcase, test_s21_memchr_various_chars);
  tcase_add_test(tcase, test_s21_memchr_large_data);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_memchr(void) {
  int number_failed;
  Suite *suite = s21_memchr_suite();
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
