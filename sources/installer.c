#include "../headers/installer.h"

int status = EXIT_FAILURE;
install i;


bool is_dir(const char *path)
{
  struct stat stats;

  stat(path, &stats);

  return S_ISDIR(stats.st_mode);
}

install *cd(const char *directory)
{
  chdir(directory);
  return &i;
}

bool suppress(const char *directory)
{
  char cmd[FILENAME_MAX];

  if(is_dir(directory))
  {
    snprintf(cmd,FILENAME_MAX,"rm -rf %s",directory);
    if(system(cmd) == 0)
    {
      success("The directory has been removed successfully");
      return true;
    }
    danger("Failed to remove the directory");
    return false;
  }
  else if(access(directory,F_OK) ==0)
  {
    return remove(directory)== 0;
  }
  die("No such file or directory");
}

install *Install(void)
{
  i.clone     = &clone;
  i.checkout  = &checkout;
  i.execute   = &execute;
  i.exist     = &exist;
  i.done      = &done;
  i.rm        = &rm;
  i.cd        = &cd;
  i.suppress  = &suppress;
  return &i;
}

int done(void(*clean)(void))
{
  clean();
  return status;
}

install *rm(const char *filename)
{
  suppress(filename);

  return &i;
}

install *exist(const char *filename)
{
  if(access(filename,F_OK)== 0)
  {
    status = EXIT_SUCCESS;
    success("The file exist on the system");
  }else
  {
    status  = EXIT_FAILURE;
    danger("The filename has been not found on the system");
  }
  return &i;
}

install *checkout(const char *path,const char *branch)
{
  char cmd[FILENAME_MAX];
  snprintf(cmd,FILENAME_MAX,"git checkout %s",branch);
  cd(path);
  if(execute(cmd) != NULL)
  {
    status = EXIT_SUCCESS;
    success("You have successfully changing of branch");
  }else
  {
    status = EXIT_FAILURE;
    danger("You have not changing the branch");
  }
  return &i;
}
install *clone(const char *repo,const char *path,const char *options)
{
  char cmd[FILENAME_MAX];
  snprintf(cmd,FILENAME_MAX,"git clone %s %s %s" ,repo,path,options);
  if(is_dir(path))
  {
    suppress(path);
  }
  if(execute(cmd) != NULL)
  {
    status= EXIT_SUCCESS;
    success("You have successfully cloned the repository");
  }else
  {
    status = EXIT_FAILURE;
    die("Cloning operation has been failed");
  }
  return &i;
}
install *execute(const char *command)
{
  FILE *c = popen(command,"w");
  if(!c)
  {
    pclose(c);
    die("Failed to run the command");
  }
  if(pclose(c) != -1)
  {
    status = EXIT_SUCCESS;
    success("The command has been executed successfully");
  }else
  {
    status = EXIT_FAILURE;
    die("Failed to run the command");
  }
  return &i;
}

