#include "../../headers/unit.h"
#include <math.h>

int main(void)
{
  return Unit()
    ->capture(hypot(3,4))
    ->equal(5)
    ->status();
}

