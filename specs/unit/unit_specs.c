#include "../../headers/unit.h"

int main(void)
{
  return Unit()
    ->ok(true)->ko(false)
    ->found("a","a")
    ->has("linux is super","linux")
    ->capture(5)
    ->inferior(10)
    ->superior(4)
    ->beetween(4,10)
    ->status();
}
