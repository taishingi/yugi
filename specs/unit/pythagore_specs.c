#include "../../headers/unit.h"
#include <math.h>


unit *pythagore(unit *u)
{
  return u->capture(hypot(3,4))->equal(5);
}

unit *thales(unit *u)
{
  return u->capture(4*7.5)->equal(6*5);
}

unit *major(unit *u)
{
  return u->capture(18)->beetween(17,100);
}

int main(void)
{
  return Unit()
    ->scenario("Test the pytagore theorem",pythagore)
    ->scenario("Test the thales theorem",thales)
    ->scenario("Test the is major",major)
    ->status();
}

