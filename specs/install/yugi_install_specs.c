#include "../../headers/installer.h"

void clean(void)
{
  success("done");
}
int main(void)
{
  return installer()
    ->clone("/var/home/juwishmaster/.github/yugi","/tmp/yugi","")
    ->cd("/tmp/yugi")
    ->execute("cmake . && make")
    ->rm("/tmp/yugi")
    ->done(clean);
}
