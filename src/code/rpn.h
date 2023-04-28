#ifndef SRC_RPN_H_
#define SRC_RPN_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_struct {
  int num;
  int size;
  int filled;
  char **strings;

} str_stack;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef F_MAX
#define F_MAX 24
#endif

#ifndef BUF_LEN
#define BUF_LEN 255
#endif

void pop(str_stack *A, char *dest);

int rpn(char *src, char *dest, str_stack *A);

void push(str_stack *A, char *src);

int check_exp(char *src);

void bin_by_priority(str_stack *A);

void clean_stack(str_stack *A);

int create_stack(int num, int size, str_stack *result);

int check_if_smth_is_in_list(char *smth, char **list, int list_lenght);

void remove_spaces(char *s);

void calc_result(str_stack *A, char *dest);

void bin_calc(char bin_op, char *num1, char *num2, char *dest);

void replace_in_stack(str_stack *A, char *smth, int n);

void calc_handler(str_stack *A, int n, char *dest, long double x);

long double bin_op(char op, long double n1, long double n2);

long double prefix_op(char *op, long double n);

long double pi_handler(int flag, char *n);

int word_plus_or_minus(char *smth, char *word);

void paste_on_index(char *src, char paste, int index);

void insert_at_sign(char *src);

void replace_unary(char *src, char rep, char with);

void prepare_expression(char *src);

int priority_handler(char *src, str_stack *stack, str_stack *out);

int check_brack(char *src, int i, str_stack *stack, str_stack *out);

void add_op_to_stack(int op, str_stack *stack, str_stack *out);

int check_priority(int op, char stack);

int get_element(char *src, int i, char *dest);

int check_brackets(char c);

int check_bin_op(char c);

#endif  // SRC_RPN_H_
