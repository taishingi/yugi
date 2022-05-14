#include "../../headers/installer.h"

void clean(void)
{
  success("done");
}
int main(void)
{
  return
    Install("Check if yugi can be installed")
    ->clone("https://github.com/shingitai/yugi.git","/tmp/yugi","")
    ->cd("/tmp/yugi")
    ->execute("cmake . && make")
    ->rm("/tmp/yugi")
    ->done(clean);
}
