#include "test.h"

// верно
START_TEST(test_x_01) {
  char *buffer = calloc(255, sizeof(char));
  char *smth = calloc(255, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "2 * x+15");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 15);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "45");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

//верно
START_TEST(test_x_02) {
  char *buffer = calloc(255, sizeof(char));
  char *smth = calloc(255, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "153*x+12");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0.1);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "27.3");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_x_03) {
  char *buffer = calloc(255, sizeof(char));
  char *smth = calloc(255, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "x^2+12");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 5);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "37");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// хз
START_TEST(test_x_04) {
  char *buffer = calloc(255, sizeof(char));
  char *smth = calloc(255, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "5* x+2*x^2-cos(-x)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 2.3);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "21.08");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// хз
START_TEST(test_x_05) {
  char *buffer = calloc(255, sizeof(char));
  char *smth = calloc(255, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "pi*x");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 3.01);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "9.4561938873053");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

void test2(SRunner *runner) {
  Suite *tests = suite_create("test2");
  tests = add_test(tests, test_x_01);
  tests = add_test(tests, test_x_02);
  tests = add_test(tests, test_x_03);
  tests = add_test(tests, test_x_04);
  tests = add_test(tests, test_x_05);
  srunner_add_suite(runner, tests);
}