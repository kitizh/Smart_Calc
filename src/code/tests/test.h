#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdio.h>

#include "../rpn.h"

Suite *add_test(Suite *suite, const TTest *test);

void test1(SRunner *runner);
void test2(SRunner *runner);

#endif  // SRC_TEST_H_
