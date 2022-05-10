#ifndef YUBEL_LIBRARY_H
#define YUBEL_LIBRARY_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "../headers/colors.h"

extern bool before_all_called;
extern double assertions;
extern double failures;
extern int status;
extern char bar_success[FILENAME_MAX];
extern char bar_failure[FILENAME_MAX];
extern void before_all(void);
extern void before(void);
extern void after(void);
extern void after_all(void);
extern FILE *foh;

#define repeat(input, count)          \
    for (int i = 0; i < count; i++)   \
    {                                 \
        fprintf(stdout, "%s", input); \
    }
#define immunity()                                                                                                                                                                                                                                                                               \
    if (failures)                                                                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                                                            \
        fprintf(stdout, "\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                                \
        repeat("\033[1;32m#\033[030m", (assertions / (assertions / failures) * 100) / 3) repeat("\033[1;31m#\033[030m", (failures / (failures + assertions) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m %0.f\033[1,37m\033[1;37m ]\033[30m\n\n", assertions, failures); \
    }                                                                                                                                                                                                                                                                                            \
    else                                                                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                                                            \
        fprintf(stdout, "\n\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                              \
        repeat("\033[1;32m#", (assertions / (assertions + failures) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m%0.f \033[1;37m]\033[30m\n\n", assertions, failures);                                                                                                    \
    }                                                                                                                                                                                                                                                                                            \
    after_all();
#define check(test, s, f)           \
    if (before_all_called == false) \
    {                               \
        before_all();               \
        before();                   \
        before_all_called = true;   \
    }                               \
    else                            \
    {                               \
        before();                   \
    }                               \
    if (test)                       \
    {                               \
        assertions++;               \
        success(s);                 \
        status = EXIT_SUCCESS;      \
    }                               \
    else                            \
    {                               \
        failures++;                 \
        danger(f);                  \
    }                               \
    after();                        \
    if (status)                     \
    {                               \
        immunity();                 \
        exit(status);               \
    };


#define IS_OK "The actual value match true"
#define IS_KO "The actual value match false"
#define IS_EQUALS "The numbers are equals"
#define IS_NOT_EQUALS "The numbers are not equals"
#define IS_IDENTICAL "The strings are identical"
#define IS_NOT_IDENTICAL "The strings are different"
#define THEORY_IS_TRUE "The theory is true"
#define THEORY_IS_FALSE "The theory is false"
#define IS_DEF "The value has been defined successfully"
#define IS_NOT_DEF "The value has not been defined"
#define IS_EMPTY "The value is empty"
#define IS_NOT_EMPTY "The value is not empty"
#define IS_FULL "The value is at the maximum value"
#define IS_NOT_FULL "The value is not at the maximum value"
#define IS_NOT "The value is not equal to the expected value"
#define IS_NO_NOT "The value is equal to the expected value"
#define IS_IS "The value is equal to the expected value"
#define IS_NOT_IS "The value is not equal to the expected value"

#define ok(actual) check((actual), IS_OK, IS_KO);
#define ko(actual) check(!(actual), IS_KO, IS_OK);
#define equals(actual, expected) check((actual) == (expected), IS_EQUALS, IS_NOT_EQUALS);
#define unequals(actual, expected) check((actual) != (expected), IS_EQUALS, IS_NOT_EQUALS);
#define identical(actual, expected) check(strcmp((actual), (expected)) == 0, IS_IDENTICAL, IS_NOT_IDENTICAL);
#define different(actual, expected) check(strcmp((actual), (expected)) != 0, IS_NOT_IDENTICAL, IS_IDENTICAL);
#define def(actual) check((actual) != NULL, IS_DEF, IS_NOT_DEF);
#define undef(actual) check((actual) == NULL, IS_NOT_DEF, IS_DEF);
#define empty(actual) check(strcmp((actual), "") == 0, IS_EMPTY, IS_NOT_EMPTY);
#define full(actual, max)                                     \
    if ((max))                                                \
    {                                                         \
        check(((actual) / (max)) == 1, IS_FULL, IS_NOT_FULL); \
    };
#define scenario(description, f) \
    title(description);           \
    f();
#define theory(description, expected, f) title(description); check((expected) == (f()), THEORY_IS_TRUE, THEORY_IS_FALSE);
#define is(actual, expected) check(actual == expected, IS_IS, IS_NOT_IS);

char *oh_history_file(void);
int run(int argc, const char **argv);
bool found(const char *a, const char *b);
bool has(const char *x, const char *needle);
bool oh_execute_last_command(void);
FILE *get(const char *filename, const char *mode);
bool has_oh_files(int argc, const char **argv);
const char *oh_file_path(const char *filename);
bool oh(const char *filename);
int oh_close();
bool is_oh(const char *filename);
bool oh_exec(const char *cmd);
#endif

