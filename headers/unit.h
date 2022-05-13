#ifndef YUBEL_LIBRARY_H
#define YUBEL_LIBRARY_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "../headers/colors.h"

#define IS_OK "The actual value match true"
#define IS_KO "The actual value match false"
#define IS_EQUALS "The numbers are equals"
#define NOT_EQUALS "The numbers are not equals"
#define IS_IDENTICAL "The strings are identical"
#define IS_NOT_IDENTICAL "The strings are different"
#define THEORY_IS_TRUE "The theory is true"
#define THEORY_IS_FALSE "The theory is false"
#define IS_DEF "The value has been defined successfully"
#define IS_NOT_DEF "The value has not been defined"
#define IS_EMPTY "The value is empty"
#define IS_BEETWEEN "The value is beetween expected values"
#define NOT_BEETWEEN "The value is not beetween the expected values"
#define IS_NOT_EMPTY "The value is not empty"
#define IS_FULL "The value is at the maximum value"
#define IS_NOT_FULL "The value is not at the maximum value"
#define IS_NOT "The value is not equal to the expected value"
#define IS_NO_NOT "The value is equal to the expected value"
#define IS_IS "The value is equal to the expected value"
#define IS_FOUND  "The value has been found"
#define NOT_FOUND  "The value has not been found"
#define IS_NOT_IS "The value is not equal to the expected value"
#define HAS      "The search value has been found"
#define HAS_NOT  "The search value has not been found"
#define IS_SUPERIOR "The value is superior has the expected value"
#define NOT_SUPERIOR "The value is inferior to the expected value"
#define IS_INFERIOR "The value is inferior has the expected value"
#define NOT_INFERIOR "The value is superior to the expected value"

typedef struct unit unit;
struct unit
{
  double assertions;
  double failures;
  double captured;

  /**
   *
   * @brief Check if the value is equal to true
   *
   * @param actual The value to check
   *
   * @return *unit
   *
   **/
  unit *(*ok)(bool actual);

  /**
   *
   * @brief check if the value return false
   *
   * @param actual The value to check
   *
   * @return *unit
   *
   */
  unit *(*ko)(bool actual);

  unit *(*found)(const char *a, const char *b);

  unit *(*has)(const char *actual, const char *needle);

  unit *(*capture)(double number);

  unit *(*beetween)(double min,double max);

  unit *(*inferior)(double max);
  unit *(*equal)(double expected);

  unit *(*superior)(double min);

  int (*status)(void);

};

int status(void);

unit *Unit(void);

unit *ok(bool actual);

unit *equal(double expected);

unit *ko(bool actual); 

unit *capture(double number);

unit *beetween(double min,double max);

unit *inferior(double max);

unit *superior(double min);

unit *has(const char *actual, const char *needle);

unit *found(const char *a, const char *b);

#endif

