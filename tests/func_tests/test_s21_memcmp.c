#include "../s21_string_tests.h"

#define LEN_6 6
#define LEN_3 3
#define LEN_8 8
#define LEN_4 4
#define LEN_5 5
#define LEN_10000 10000

START_TEST(test_memcmp_equal_blocks) {
  const char str1[] = "abcdef";
  const char str2[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str1, str2, LEN_6), memcmp(str1, str2, LEN_6));
}
END_TEST

START_TEST(test_memcmp_different_blocks) {
  const char str3[] = "abcdef";
  const char str4[] = "abcdff";
  ck_assert_int_eq(s21_memcmp(str3, str4, LEN_6), memcmp(str3, str4, LEN_6));
}
END_TEST

START_TEST(test_memcmp_different_lengths) {
  const char str7[] = "abc";
  const char str8[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(str7, str8, LEN_3), memcmp(str7, str8, LEN_3));
}
END_TEST

START_TEST(test_memcmp_partial_comparison) {
  const char str9[] = "abcdefgh";
  const char str10[] = "abcdzxyz";
  ck_assert_int_eq(s21_memcmp(str9, str10, LEN_4), memcmp(str9, str10, LEN_4));
}
END_TEST

START_TEST(test_memcmp_empty_strings) {
  const char str11[] = "";
  const char str12[] = "";
  ck_assert_int_eq(s21_memcmp(str11, str12, 0), memcmp(str11, str12, 0));
}
END_TEST

START_TEST(test_memcmp_empty_and_non_empty) {
  const char *str13 = NULL;
  const char str14[] = "abc";
  ck_assert_int_eq(s21_memcmp(str13, str14, LEN_3), 0);
}
END_TEST

START_TEST(test_memcmp_non_empty_and_empty) {
  const char str13[] = "abc";
  const char *str14 = NULL;
  ck_assert_int_eq(s21_memcmp(str13, str14, LEN_3), 0);
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  const char str15[] = "hello";
  const char str16[] = "hello";
  ck_assert_int_eq(s21_memcmp(str15, str16, 0), memcmp(str15, str16, 0));
}
END_TEST

START_TEST(test_memcmp_first_char_different) {
  const char str19[] = "hello";
  const char str20[] = "hxllo";
  ck_assert_int_eq(s21_memcmp(str19, str20, 1), memcmp(str19, str20, 1));
}
END_TEST

START_TEST(test_memcmp_large_blocks) {
  char str21[LEN_10000] = {0};
  char str22[LEN_10000] = {0};
  memset(str21, 'a', LEN_10000);
  memset(str22, 'a', LEN_10000);
  ck_assert_int_eq(s21_memcmp(str21, str22, LEN_10000),
                   memcmp(str21, str22, LEN_10000));
}
END_TEST

START_TEST(test_memcmp_single_char) {
  const char str23[] = "a";
  const char str24[] = "b";
  ck_assert_int_eq(s21_memcmp(str23, str24, 1), memcmp(str23, str24, 1));
}
END_TEST

Suite *memcmp_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memcmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcmp_equal_blocks);
  tcase_add_test(tc_core, test_memcmp_different_blocks);
  tcase_add_test(tc_core, test_memcmp_different_lengths);
  tcase_add_test(tc_core, test_memcmp_partial_comparison);
  tcase_add_test(tc_core, test_memcmp_empty_strings);
  tcase_add_test(tc_core, test_memcmp_empty_and_non_empty);
  tcase_add_test(tc_core, test_memcmp_non_empty_and_empty);
  tcase_add_test(tc_core, test_memcmp_zero_length);
  tcase_add_test(tc_core, test_memcmp_first_char_different);
  tcase_add_test(tc_core, test_memcmp_large_blocks);
  tcase_add_test(tc_core, test_memcmp_single_char);

  suite_add_tcase(s, tc_core);

  return s;
}

int test_s21_memcmp(void) {
  int failed_count;
  Suite *s;
  SRunner *sr;

  s = memcmp_suite();
  sr = srunner_create(s);

  system("mkdir -p tests/logs");
  char full_filename[1024];
  sprintf(full_filename, "tests/logs/%s.log", __FILE_NAME__);
  srunner_set_log(sr, full_filename);

  srunner_run_all(sr, CK_ENV);
  failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed_count == 0) ? 0 : 1;
}
