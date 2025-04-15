#include "../../s21_string.h"
#include "../s21_string_tests.h"

#define LEN 100

START_TEST(normal_data) {
  char str1[LEN] = "Hello world";
  char str2[LEN] = "aeiou";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(no_match) {
  char str1[LEN] = "Hello world";
  char str2[LEN] = "xyz";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(full_match) {
  char str1[LEN] = "aaaaa";
  char str2[LEN] = "a";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(empty_str1) {
  char str1[LEN] = "";
  char str2[LEN] = "xyz";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(empty_str2) {
  char str1[LEN] = "Hello world";
  char str2[LEN] = "";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(empty_both) {
  char str1[LEN] = "";
  char str2[LEN] = "";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(special_characters) {
  char str1[LEN] = "Hello, world!";
  char str2[LEN] = "!, ";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
}
END_TEST

START_TEST(long_str) {
  char *str1 = calloc(LEN * LEN * LEN, sizeof(char));
  memset(str1, 'a', LEN * LEN * LEN - 1);
  str1[LEN * LEN] = 'b';
  char str2[LEN] = "b";
  s21_size_t s21_res = s21_strcspn(str1, str2);
  s21_size_t orig_res = strcspn(str1, str2);
  ck_assert_uint_eq(s21_res, orig_res);
  free(str1);
}
END_TEST

int test_s21_strcspn(void) {
  Suite *s1 = suite_create("s21_strcspn");
  TCase *tc1_1 = tcase_create("s21_strcspn");
  SRunner *sr = srunner_create(s1);
  int nf;

  /* User-specified pre-run code */
  system("mkdir -p tests/logs");
  char full_filename[1024];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, normal_data);
  tcase_add_test(tc1_1, no_match);
  tcase_add_test(tc1_1, full_match);
  tcase_add_test(tc1_1, empty_str1);
  tcase_add_test(tc1_1, empty_str2);
  tcase_add_test(tc1_1, empty_both);
  tcase_add_test(tc1_1, special_characters);
  tcase_add_test(tc1_1, long_str);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
