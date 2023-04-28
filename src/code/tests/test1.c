#include "test.h"

// верно
START_TEST(test_01) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "32.42 + 4443-2.3234");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "4473.0966");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// хз
START_TEST(test_02) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "15*3e + 56");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "101");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_03) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "3+4*2 / (1-5) ^2");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "3.5");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_04) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "342/3 - 2");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "112");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_05) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "112-236mod3*5+3");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "105");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_06) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "cos(12/15)+ln(4)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "2.0830010704671");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_07) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "(324+32*2)*sin(324-45)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "219.640121629928");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// тут минуса не должно быть
START_TEST(test_08) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "15*(-cos(4))");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "9.804654312954");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_09) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-2! + pi");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// неверно
START_TEST(test_10) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "pi");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "3.14159265358979");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_11) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "pi * 1");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "3.1415926535898");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_12) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "36:3(8-2) /6");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_13) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "36/3*(8-2) /6");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "12");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_14) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "0.1 + 0.2");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "0.3");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_15) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "25+-20");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_16) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "25@+-20");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_17) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "255*(34+23/(2+2))");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "10136.25");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_18) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-25+345*(-2)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-715");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_19) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "*342-23");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_20) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-20*(-23)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "460");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_21) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "tan(sqrt(pi))");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-4.8915003797971");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_22) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "tan$(sqrt(pi))");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_23) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "tap(16)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// неверно
START_TEST(test_24) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "+asin(16)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// неверно
START_TEST(test_25) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "atan(+pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "1.2626272556789");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_26) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "atan(pi)(-");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_27) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "log(2+5)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "0.8450980400143");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_28) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "15^2^2");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "50625");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_29) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "log(125)*1.422");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "2.9818060384975");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_30) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "6!");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "720");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_31) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "26!");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "inf");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// хрень
START_TEST(test_32) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-pi");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-3.14159265358979");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_33) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "sin(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-0");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_34) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "sin(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "0");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_35) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "cos(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-1");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// хрень
START_TEST(test_36) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "cos(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-1");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_37) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "sqrt(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "1.7724538509055");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_38) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "sqrt(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_39) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "tan(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-0");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_40) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "tan(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "0");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_41) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-pi * 2");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-6.2831853071796");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

//можно error а не nan
START_TEST(test_42) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "asin(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// err/nan
START_TEST(test_43) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "asin(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_44) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "atan(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "1.2626272556789");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// нет минуса
START_TEST(test_45) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "atan(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-1.2626272556789");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// nan или err
START_TEST(test_46) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "acos(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// nan или pi
START_TEST(test_47) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "acos(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_48) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "ln(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "1.1447298858494");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_49) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "ln(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_50) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "log(pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "0.4971498726941");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_51) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "log(-pi)");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "nan");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_52) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "cos(pi)*sin(34)+ln(2.345) * (234.2-221.6)/2 mod 3 * 342");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "809.8050442437554");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

// верно
START_TEST(test_53) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "234.23 mod 32.3");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "8.13");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_54) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "2345 - * 32 ");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_55) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "34)-23");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_56) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "3.533-");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_57) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "+3.533");
  x = rpn(smth, buffer, &str_for_out);

  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "3.533");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_58) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, "-3.533");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "-3.533");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

START_TEST(test_59) {
  char *buffer = calloc(BUF_LEN, sizeof(char));
  char *smth = calloc(BUF_LEN, sizeof(char));
  str_stack str_for_out;
  int x = 0;
  create_stack(60 * 2, 300, &str_for_out);
  strcpy(smth, ")2+3(");
  x = rpn(smth, buffer, &str_for_out);
  calc_handler(&str_for_out, x, buffer, 0);

  // ck_assert_int_eq(x, 0);

  ck_assert_str_eq(buffer, "ERROR");
  free(buffer);
  free(smth);
  clean_stack(&str_for_out);
}
END_TEST

void test1(SRunner *runner) {
  Suite *tests = suite_create("test1");
  tests = add_test(tests, test_01);
  tests = add_test(tests, test_02);
  tests = add_test(tests, test_03);
  tests = add_test(tests, test_04);
  tests = add_test(tests, test_05);
  tests = add_test(tests, test_06);
  tests = add_test(tests, test_07);
  tests = add_test(tests, test_08);
  tests = add_test(tests, test_09);
  tests = add_test(tests, test_10);
  tests = add_test(tests, test_11);
  tests = add_test(tests, test_12);
  tests = add_test(tests, test_13);
  tests = add_test(tests, test_14);
  tests = add_test(tests, test_15);
  tests = add_test(tests, test_16);
  tests = add_test(tests, test_17);
  tests = add_test(tests, test_18);
  tests = add_test(tests, test_19);
  tests = add_test(tests, test_20);
  tests = add_test(tests, test_21);
  tests = add_test(tests, test_22);
  tests = add_test(tests, test_23);
  tests = add_test(tests, test_24);
  tests = add_test(tests, test_25);
  tests = add_test(tests, test_26);
  tests = add_test(tests, test_27);
  tests = add_test(tests, test_28);
  tests = add_test(tests, test_29);
  tests = add_test(tests, test_30);
  tests = add_test(tests, test_31);
  tests = add_test(tests, test_32);
  tests = add_test(tests, test_33);
  tests = add_test(tests, test_34);
  tests = add_test(tests, test_35);
  tests = add_test(tests, test_36);
  tests = add_test(tests, test_37);
  tests = add_test(tests, test_38);
  tests = add_test(tests, test_39);
  tests = add_test(tests, test_40);
  tests = add_test(tests, test_41);
  tests = add_test(tests, test_42);
  tests = add_test(tests, test_43);
  tests = add_test(tests, test_44);
  tests = add_test(tests, test_45);
  tests = add_test(tests, test_46);
  tests = add_test(tests, test_47);
  tests = add_test(tests, test_48);
  tests = add_test(tests, test_49);
  tests = add_test(tests, test_50);
  tests = add_test(tests, test_51);
  tests = add_test(tests, test_52);
  tests = add_test(tests, test_53);
  tests = add_test(tests, test_54);
  tests = add_test(tests, test_55);
  tests = add_test(tests, test_56);
  tests = add_test(tests, test_57);
  tests = add_test(tests, test_58);
  tests = add_test(tests, test_59);
  srunner_add_suite(runner, tests);
}
