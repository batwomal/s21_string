#include "../s21_string_tests.h"

START_TEST(test_s21_memcpy_empty) {
  const char src[] = "Hello";
  char dest[6] = {0};
  void *res = s21_memcpy(dest, src, 0);
  void *expected = memcpy(dest, src, 0);
  ck_assert_ptr_eq(res, expected);
  ck_assert_str_eq(dest, "");
}
END_TEST

START_TEST(test_s21_memcpy_full_copy) {
  char src[] = "Hello, World!";
  char dest[20] = {0};
  void *res = s21_memcpy(dest, src, strlen(src) + 1);
  void *expected = memcpy(dest, src, strlen(src) + 1);
  ck_assert_ptr_eq(res, expected);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_memcpy_partial_copy) {
  const char src[] = "Hello, World!";
  char dest[6] = {0};
  void *res = s21_memcpy(dest, src, 5);
  void *expected = memcpy(dest, src, 5);
  ck_assert_ptr_eq(res, expected);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_s21_memcpy_overlap) {
  char buffer[] = "Hello, World!";
  void *res = s21_memcpy(buffer + 6, buffer, 6);
  void *expected = memcpy(buffer + 6, buffer, 6);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memcpy_zero_size) {
  const char src[] = "Hello";
  char dest[6] = {0};
  void *res = s21_memcpy(dest, src, 0);
  void *expected = memcpy(dest, src, 0);
  ck_assert_ptr_eq(res, expected);
  ck_assert_str_eq(dest, "");
}
END_TEST

START_TEST(test_s21_memcpy_overlap_shifted) {
  char buffer[] = "Hello, World!";
  void *res = s21_memcpy(buffer + 1, buffer, 5);
  void *expected = memcpy(buffer + 1, buffer, 5);
  ck_assert_ptr_eq(res, expected);
}
END_TEST

START_TEST(test_s21_memcpy_null_characters) {
  char src[] = {0, 1, 2, 3, 4};
  char dest[5] = {0};
  void *res = s21_memcpy(dest, src, 5);
  void *expected = memcpy(dest, src, 5);
  ck_assert_ptr_eq(res, expected);
  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(dest[i], src[i]);
  }
}
END_TEST

START_TEST(test_s21_memcpy_large_data) {
  char *src = malloc(1000000);
  char *dest = malloc(1000000);
  memset(src, 'A', 1000000);
  void *res = s21_memcpy(dest, src, 1000000);
  void *expected = memcpy(dest, src, 1000000);
  ck_assert_ptr_eq(res, expected);
  for (int i = 0; i < 1000000; i++) {
    ck_assert_int_eq(dest[i], 'A');
  }
  free(src);
  free(dest);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_s21_memcpy_empty);
  tcase_add_test(tcase, test_s21_memcpy_full_copy);
  tcase_add_test(tcase, test_s21_memcpy_partial_copy);
  tcase_add_test(tcase, test_s21_memcpy_overlap);
  tcase_add_test(tcase, test_s21_memcpy_zero_size);
  tcase_add_test(tcase, test_s21_memcpy_overlap_shifted);
  tcase_add_test(tcase, test_s21_memcpy_null_characters);
  tcase_add_test(tcase, test_s21_memcpy_large_data);

  suite_add_tcase(suite, tcase);
  return suite;
}

int test_s21_memcpy(void) {
  int number_failed;
  Suite *suite = s21_memcpy_suite();
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
