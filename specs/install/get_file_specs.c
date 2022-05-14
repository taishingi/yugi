#include "../../headers/installer.h"

void clean(void)
{
  success("done");
}

int main(void)
{
  return
    Install("Download linux readme file")
    ->cd("/tmp")
    ->execute("wget https://github.com/torvalds/linux/blob/master/README")
    ->exist("README")
    ->rm("README")
    ->done(clean);
}
