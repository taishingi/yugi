#include "../../headers/unit.h"
int main(void)
{
  return Unit()->capture(4*7.5)->equal(6*5)->status();
}
