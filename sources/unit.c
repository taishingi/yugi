#include "../headers/unit.h"

unit u;
unit *Unit(void)
{
  u.assertions = 0;
  u.failures = 0;
  u.captured = 0;
  u.ok = &ok;
  u.ko = &ko;
  u.has = &has;
  u.equal = &equal;
  u.found = &found;
  u.capture = &capture;
  u.beetween = &beetween;
  u.superior = &superior;
  u.inferior = &inferior;
  u.status = &status;
  u.theory = &theory;
  u.scenario  =&scenario;
  return &u;
}

unit *scenario(const char *description,unit *(*f)(unit *u))
{
  title(description);
  return f(&u);
}
unit *theory(const char *description,int expected, int (*check)(void))
{
  title(description);
  if(expected == check())
  {
    success(THEORY_IS_TRUE);
    u.assertions++;
  }else
  {
    danger(THEORY_IS_FALSE);
    u.failures++;
  }
  return &u;
}
unit *ok(bool actual)
{
  if(actual)
  {
    success(IS_OK);
    u.assertions++;
  }else
  {
    danger(IS_KO);
    u.failures++;
  }
  return &u;
}

unit *ko(bool actual)
{
  if(!actual)
  {
    u.assertions++;
    success(IS_KO);
  }else
  {
    danger(IS_OK);
    u.failures++;
  }
  return &u;
}

unit *capture(double data)
{
  u.captured  = data;
  return &u;
}

int status(void)
{
  fprintf(stdout,"\033[1;37mAssertions : \033[1;32m%0.f\033[30m \033[1;37mFailures : \033[1;31m%0.f\033[30m\n",u.assertions,u.failures);
  return u.failures > 0  ? EXIT_FAILURE : EXIT_SUCCESS;
}

unit *inferior(double max)
{
  if(u.captured < max)
  {
    success(IS_INFERIOR);
    u.assertions++;
  }else
  {
    danger(NOT_INFERIOR);
    u.failures++;
  }
  return &u;
}

unit *superior(double min)
{
  if(u.captured > min)
  {
    success(IS_SUPERIOR);
    u.assertions++;
  }else
  {
    danger(NOT_SUPERIOR);
    u.failures++;
  }
  return &u;
}

unit *beetween(double min,double max)
{
  if(u.captured < max && u.captured > min)
  {
    success(IS_BEETWEEN);
    u.assertions++;
  }
  else
  {
    danger(NOT_BEETWEEN);
    u.failures++;
  }
  return &u;
}
unit *equal(double expected)
{
  if(u.captured == expected)
  {
    success(IS_EQUALS);
    u.assertions++;
  }else
  {
    danger(NOT_EQUALS);
    u.failures++;
  }
  return &u;
}

unit *found(const char *a, const char *b)
{
  if(strcmp(a, b) == 0)
  {
    success(IS_FOUND);
    u.assertions++;
  }
  else
  {
    danger(NOT_FOUND);
    u.failures++;
  }
  return &u;
}

unit *has(const char *actual, const char *needle)
{
  if(strstr(actual, needle) != NULL)
  {
    success(HAS);
    u.assertions++;
  }else
  {
    danger(HAS_NOT);
    u.failures++;
  }
  return &u;
}

