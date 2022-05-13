#ifndef YUBEL_INSTALL
#define YUBEL_INSTALL

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>

#include "../headers/colors.h"

extern int status;
typedef struct install install;
struct install
{

  bool (*suppress)(const char *directory);

  /**
   *
   * Change the repository branch
   *
   * @param path The repository directory path
   * @param branch The branch name
   *
   * @return *install
   *
   **/
  install *(*checkout)(const char *path,const char *branch);

  /**
   *
   * clone a remote repository inthe local disk
   *
   * @param url The url of the repository
   * @param path The repo clone path
   * @param options The options to clone the repo
   *
   * @return *install
   *
   **/
  install *(*clone)(const char *url,const char *path,const char *options);

  /**
   *
   * @brief Change of directory
   *
   * @param directory the directory path
   *
   * @return *install
   *
   **/
  install *(*cd)(const char *directory);

  /**
   *
   * Check if the file exist
   *
   * @param filename The file to check
   *
   * @return *install
   *
   **/
  install *(*exist)(const char *filename);

  /**
   *
   * @brief remove a file
   *
   * @param filename The filename
   *
   * @return *install
   *
   **/
  install *(*rm)(const char *filename);

  /**
   *
   * Execute a shell command
   *
   * @param command The command to execute
   *
   * @return *install
   *
   **/
  install *(*execute)(const char *command);

  /**
   *
   * Get the status of the command
   *
   * @param f A pointer function
   *
   * @return int the status code
   *
   **/
  int (*done)(void(*f)(void));

};

install *cd(const char *directory);

/**
 *
 * End of the command
 *
 * @param clean The function to clean that has been done to testing
 *
 * @return int the status code
 *
 **/
int done(void(*clean)(void));

/**
 *
 * Get the instance
 *
 * @return *install
 *
 **/
install *Install(void);

/**
 *
 * Change of the branch
 *
 * @param path  The repository path
 * @param branch The repository branch
 *
 * @return *install
 *
 **/
install *checkout(const char *path,const char *branch);

/**
 *
 * Remove a file if exist
 *
 * @param filename THe filename
 *
 * @return *install
 *
 **/
install *rm(const char *filename);

/**
 *
 * Get the program
 *
 * @param url The url to repository
 * @param path The path to store the reposititory
 * @param options The options to clone
 *
 * @return *install
 *
 **/
install *clone(const char *repo,const char *path,const char *options);

/**
 *
 * The command to execute
 *
 * @param command The command to execute
 *
 * @return *install
 *
 **/
install *execute(const char *command);

/**
 *
 * Check if the file exist
 *
 * @param filename The
 *
 * @return *install
 *
 **/
install *exist(const char *filename);

bool is_dir(const char *path);

bool suppress(const char *directory);

#endif

