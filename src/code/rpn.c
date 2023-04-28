#include "rpn.h"

int rpn(char *src, char *dest, str_stack *str_for_out) {
  char *temp_buf = calloc(50, sizeof(char));
  str_stack stack;
  int err = 0;
  create_stack(120, 300, &stack);
  prepare_expression(src);
  err = check_exp(src);
  if (!err) {
    err = priority_handler(src, &stack, str_for_out);
  }
  if (!err) {
    while (stack.filled > 0) {
      memset(temp_buf, 0, 50);
      pop(&stack, temp_buf);
      push(str_for_out, temp_buf);
    }
  } else {
    strcpy(dest, "ERROR");
  }
  clean_stack(&stack);
  free(temp_buf);
  return str_for_out->filled;
}

int check_exp(char *src) {
  int err = 0;
  int len = (int)strlen(src);
  int brackets = 0;
  for (int i = 0; i < len; i++) {
    if (src[i] == '(') {
      brackets++;
    } else if (src[i] == ')') {
      brackets--;
    }
  }
  if ((check_bin_op(src[0]) > 2) || (check_bin_op(src[len - 1])) || brackets) {
    err = 1;
  }
  return err;
}

int check_bin_op(char c) {
  char *bin_op[] = {"+", "-", "*", "/", "m", "^", "@"};
  char *temp = calloc(50, sizeof(char));
  sprintf(temp, "%c", c);
  int res = (check_if_smth_is_in_list(temp, bin_op, 7));
  if (temp[0] == '(') {
    res = -1;
  }
  free(temp);
  return res;
}

int check_brackets(char c) {
  char *brackets[] = {"(", ")"};
  char *temp = calloc(50, sizeof(char));
  sprintf(temp, "%c", c);
  int res = (check_if_smth_is_in_list(temp, brackets, 2));
  free(temp);
  return res;
}

int get_element(char *src, int i, char *dest) {
  int j = 0;
  int end = 0;
  int len = (int)strlen(src);
  while (i + j < len && !end) {
    if (!check_bin_op(src[i + j]) && !check_brackets(src[i + j])) {
      dest[j] = src[i + j];
      j++;
    } else {
      end = 1;
    }
  }
  if (src[i] == '#') {
    dest[0] = '+';
  } else if (src[i] == '$') {
    dest[0] = '-';
  }
  return i + j;
}

// 0 если в стеке менее приоритетная 1 в ином случае
int check_priority(int op, char stack) {
  int res = 0;
  int op2 = check_bin_op(stack);
  if ((op < 3 && op2 > 0) || (op < 6 && op2 > 2) || (op2 > 5) || op2 == 0) {
    res = 1;
  }
  return res;
}

void add_op_to_stack(int op, str_stack *stack, str_stack *out) {
  char *bin_op[] = {"+", "-", "*", "/", "m", "^", "@"};
  char *temp_buf = calloc(50, sizeof(char));
  int end = 0;
  while (stack->filled > 0 && !end) {
    pop(stack, temp_buf);
    if (check_priority(op, temp_buf[0])) {
      push(out, temp_buf);
    } else {
      push(stack, temp_buf);
      end = 1;
    }
    memset(temp_buf, 0, 50);
  }
  push(stack, bin_op[op - 1]);
  free(temp_buf);
}

int check_brack(char *src, int i, str_stack *stack, str_stack *out) {
  char *temp_buf = calloc(50, sizeof(char));
  int res = 0;
  int err = 0;
  int end = 0;
  if (src[i] == '(') {
    res = 1;
    push(stack, "(");
  } else if (src[i] == ')') {
    res = 2;
    while (!err && !end) {
      pop(stack, temp_buf);
      if (temp_buf[0] == '(') {
        end = 1;
      } else if (stack->filled == 0) {
        err = 1;
      } else {
        push(out, temp_buf);
      }
      memset(temp_buf, 0, 50);
    }
    if (err) {
      res = -1;
    }
  }
  free(temp_buf);
  return res;
}

int priority_handler(char *src, str_stack *stack, str_stack *out) {
  size_t len = strlen(src);
  size_t i = 0;
  int op = 0;
  int err = 0;
  int prev_is_op = 0;
  char *element = calloc(50, sizeof(char));
  int prev_is_brack = 1;  // флаг допустимости унарных знаков
  while (i < len && !err && prev_is_brack != -1) {
    op = check_bin_op(src[i]);
    if (op > 0) {
      i++;
      if (prev_is_op) {
        err = 1;
      } else {
        prev_is_op = 1;
        add_op_to_stack(op, stack, out);
        if (op == 5) {
          i += 2;
        }
      }
    }
    if (!err) {
      prev_is_brack = check_brack(src, i, stack, out);
      if (prev_is_brack == -1) {
        err = 1;
      } else {
        if (prev_is_brack > 0) {
          i++;
        }
        i = get_element(src, i, element);
        if (element[0] != 0) {
          push(out, element);
          prev_is_op = 0;
        }

        prev_is_brack = check_brack(src, i, stack, out);
        if (prev_is_brack > 0) {
          i++;
        }
        memset(element, 0, 50);
      }
    }
  }
  free(element);
  return err;
}

void prepare_expression(char *src) {
  remove_spaces(src);
  replace_unary(src, '+', '#');
  replace_unary(src, '-', '$');
  insert_at_sign(src);
}

void replace_unary(char *src, char rep, char with) {
  size_t len = strlen(src);
  for (size_t i = 0; i < len; i++) {
    if ((src[i] == rep) && ((i == 0) || (src[i - 1] == '('))) {
      src[i] = with;
    }
  }
}

void insert_at_sign(char *src) {
  size_t len = strlen(src);
  for (size_t i = len - 1; i > 0; i--) {
    if ((src[i] == '!') ||
        (((src[i - 1] == 'n') || (src[i - 1] == 'g') || (src[i - 1] == 't') ||
          (src[i - 1] == 's') || (src[i - 1] == 'i')) &&
         (src[i] == '('))) {
      paste_on_index(src, '@', i);
    }
  }
}

void paste_on_index(char *src, char paste, int index) {
  size_t len = strlen(src);
  for (size_t i = len; i > (size_t)index; i--) {
    src[i] = src[i - 1];
  }
  src[index] = paste;
}

void calc_handler(str_stack *A, int n, char *dest, long double x) {
  str_stack B;
  create_stack(n * 2, 300, &B);
  for (int i = 0; i < n; i++) {
    strcpy(B.strings[i], A->strings[i]);
  }
  B.filled = A->filled;
  for (int i = 0; i < n; i++) {
    if (B.strings[i][0] == 'x') {
      sprintf(B.strings[i], "%.15Lf", x);
    }
  }
  calc_result(&B, dest);
  clean_stack(&B);
}

void calc_result(str_stack *A, char *dest) {
  char *e;
  int max = A->filled;
  int end = 0;
  long double n1 = 0;
  if (strcmp(dest, "ERROR")) {
    memset(dest, 0, 100);
    if (max == 1) {
      if (!strcmp(A->strings[0], "pi")) {
        sprintf(A->strings[0], "%.14f", M_PI);
      } else if (!strcmp(A->strings[0], "-pi")) {
        sprintf(A->strings[0], "%.14f", -M_PI);
      }
    } else {
      bin_by_priority(A);
      if (A->filled > 1) {
        end = 1;
      }
    }
    if (!end) {
      n1 = strtold(A->strings[0], &e);
      sprintf(dest, "%.14Lf", n1);
      for (int i = (int)strlen(dest) - 1; i > 0 && !end; i--) {
        if (dest[i] == '0') {
          dest[i] = '\0';
        } else if (dest[i] == '.') {
          dest[i] = '\0';
          end = 1;
        } else {
          end = 1;
        }
      }
    } else {
      sprintf(dest, "ERROR");
    }
  }
}

void bin_by_priority(str_stack *A) {
  int max = A->filled;
  char *bin_op[] = {"+", "-", "*", "/", "^", "m", "@"};
  char *num1 = calloc(128, sizeof(char));
  char *num2 = calloc(128, sizeof(char));
  char *temp = calloc(128, sizeof(char));
  int nums = 0;
  int i = 0;
  char op = 0;
  while (i < max && max > 1) {
    if (check_if_smth_is_in_list(A->strings[i], bin_op, 7)) {
      op = A->strings[i][0];
      bin_calc(op, num1, num2, temp);
      memset(num1, 0, 60);
      memset(num2, 0, 60);
      nums = 0;
      replace_in_stack(A, temp, i - 2);
      max -= 2;
      i = 0;
    } else {
      if (nums == 0) {
        strcpy(num1, A->strings[i]);
        nums++;
      } else if (nums == 1) {
        strcpy(num2, A->strings[i]);
        nums++;
      } else {
        memset(num1, 0, 60);
        strcpy(num1, num2);
        memset(num2, 0, 60);
        strcpy(num2, A->strings[i]);
      }
      i++;
    }
  }
  free(num1);
  free(num2);
  free(temp);
}

int word_plus_or_minus(char *smth, char *word) {
  int res = 0;
  char minus_word[20] = {0};
  char plus_word[20] = {0};
  sprintf(minus_word, "-%s", word);
  sprintf(plus_word, "+%s", word);
  if (!strcmp(smth, word)) {
    res = 1;
  } else if (!strcmp(smth, minus_word)) {
    res = 2;
  } else if (!strcmp(smth, plus_word)) {
    res = 3;
  }
  return res;
}

long double pi_handler(int flag, char *n) {
  long double res = 0;
  char *e;
  if (flag) {
    if (flag == 2) {
      res = -M_PI;
    } else if (flag == 3) {
      res = +M_PI;
    } else {
      res = M_PI;
    }
  } else {
    res = strtold(n, &e);
  }
  return res;
}

void bin_calc(char op, char *num1, char *num2, char *dest) {
  int pi1 = 0;  // 0-NO 1-YES 2-MINUS 3-PLUS
  int pi2 = 0;
  long double n1 = 0;
  long double n2 = 0;
  long double res = 0;

  pi1 = word_plus_or_minus(num1, "pi");
  pi2 = word_plus_or_minus(num2, "pi");
  n1 = pi_handler(pi1, num1);
  n2 = pi_handler(pi2, num2);
  if (op == '@') {
    if (num2[0] == '!') {
      res = 1;
      if (n1 >= 0 && fmod(n1, (int)n1) < 1e-10 && n1 <= F_MAX) {
        for (int c = 1; c <= (int)n1; c++) {
          res = res * c;
        }
      } else {
        if (n1 < 0) {
          res = NAN;
        } else {
          res = +INFINITY;
        }
      }
    } else {
      res = prefix_op(num1, n2);
    }
  } else {
    res = bin_op(op, n1, n2);
  }
  sprintf(dest, "%.13Lf", res);
}

long double prefix_op(char *op, long double n) {
  long double res = 0;
  if (word_plus_or_minus(op, "cos")) {
    res = cos(n);
  } else if (word_plus_or_minus(op, "sin")) {
    res = sin(n);
  } else if (word_plus_or_minus(op, "tan")) {
    res = tan(n);
  } else if (word_plus_or_minus(op, "acos")) {
    res = acos(n);
  } else if (word_plus_or_minus(op, "asin")) {
    res = asin(n);
  } else if (word_plus_or_minus(op, "atan")) {
    res = atan(n);
  } else if (word_plus_or_minus(op, "sqrt")) {
    res = sqrt(n);
  } else if (word_plus_or_minus(op, "ln")) {
    res = log(n);
  } else if (word_plus_or_minus(op, "log")) {
    res = log10(n);
  }
  if (op[0] == '-') {
    res = -res;
  }
  return res;
}

long double bin_op(char op, long double n1, long double n2) {
  long double res = 0;
  if (op == '+') {
    res = n1 + n2;
  } else if (op == '-') {
    res = n1 - n2;
  } else if (op == '*') {
    res = n1 * n2;
  } else if (op == '/') {
    res = n1 / n2;
  } else if (op == '^') {
    res = powl(n1, n2);
  } else if (op == 'm') {
    res = fmod(n1, n2);
  }
  return res;
}

void replace_in_stack(str_stack *A, char *smth, int n) {
  for (int i = n + 1; i < A->filled; i++) {
    strcpy(A->strings[i], A->strings[i + 2]);
    memset(A->strings[i + 2], 0, 60);
  }
  memset(A->strings[n], 0, 60);
  strcpy(A->strings[n], smth);
  A->filled -= 2;
}

void remove_spaces(char *src) {
  size_t len = strlen(src);
  for (size_t i = 0; i < len; i++) {
    if (src[i] == ' ') {
      for (size_t j = i; j < len - 1; j++) {
        src[j] = src[j + 1];
      }
      src[len - 1] = '\0';
      len--;
    }
  }
}

int check_if_smth_is_in_list(char *smth, char **list, int list_lenght) {
  int res = 0;
  for (int i = 0; (i < list_lenght) && (res == 0); i++) {
    if (!strcmp(smth, list[i])) {
      res = i + 1;
    }
  }
  return res;
}

int create_stack(int num, int size, str_stack *result) {
  result->num = num;
  result->size = size;
  result->filled = 0;
  result->strings = calloc(result->num, sizeof(char *));
  if (result->strings != NULL) {
    for (int i = 0; i < result->num; i++) {
      result->strings[i] = calloc(result->size, sizeof(char));
    }
  }
  return 1;
}

void clean_stack(str_stack *A) {
  if (A) {
    if (A->strings) {
      for (int i = 0; i < A->num; i++) {
        free(A->strings[i]);
      }
      free(A->strings);
      A->strings = NULL;
    }
    A->num = 0;
    A->size = 0;
    A->filled = 0;
    A = NULL;
  }
}

void push(str_stack *A, char *src) {
  memset(A->strings[A->filled], 0, 60);
  strcpy(A->strings[A->filled], src);
  A->filled++;
}

void pop(str_stack *A, char *dest) {
  strcpy(dest, A->strings[A->filled - 1]);
  memset(A->strings[A->filled - 1], 0, 60);
  A->filled--;
}